#include <EasyEngine/eepch.h>

#include <EasyEngine/EasyEngine.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/ManagerLocator.h>
#include <ui/ShaderEditorTextArea.h>

using namespace easy_engine;

using input_manager::Key;
using input_manager::Action;
using input_manager::Modifier;

class ViewportControls : public ecs::ISystem, public event_manager::IObserver {
public:
	ViewportControls() {
		ManagerLocator::event_manager->Subscribe(
			event_manager::EventType::kKeyboard,
			this
		);
	}

	auto OnEvent(event_manager::Event event_) -> void override {
		event_buffer_.push_back(event_);
	}

	auto Update(float dt) -> void override {
		for (auto event_ : this->event_buffer_) {
			auto event = reinterpret_cast<input_manager::KeyboardEvent*>(event_.data);
			if (event->action == Action::kPressed) {
				for (auto entity : this->entities_) {
					auto maybe_transform = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					if (!maybe_transform.has_value()) continue;

					auto transform = maybe_transform.value();

					auto negativeFactor = -0.01f * dt;
					auto positiveFactor = 0.01f * dt;
					auto translateFactor = 0.5f;
					auto scaleFactor = 0.1f;

					switch (event->key) {
					case Key::kE:
					{
						auto scale = 1 + positiveFactor * scaleFactor;
						transform->ScaleMultiply(scale, scale, scale);
						break;
					}
					case Key::kQ:
					{
						auto scale = 1 - positiveFactor * scaleFactor;
						transform->ScaleMultiply(scale, scale, scale);
						break;
					}
					case Key::kW:
						transform->TranslationAdd(0, 0, negativeFactor * translateFactor);
						break;
					case Key::kS:
						transform->TranslationAdd(0, 0, positiveFactor * translateFactor);
						break;
					case Key::kA:
						transform->TranslationAdd(negativeFactor * translateFactor, 0, 0);
						break;
					case Key::kD:
						transform->TranslationAdd(positiveFactor * translateFactor, 0, 0);
						break;
					case Key::kR:
						auto rotation_direction = event->modifiers == Modifier::kControl ? -1.f : 1.f;
						transform->RotationAdd(rotation_direction * positiveFactor, ecs::component::kPivotZ);
						break;
					}
				}
			}
		}

		event_buffer_.clear();
	}
private:
	std::vector<event_manager::Event> event_buffer_;
	bool textures = true;
	std::optional<ecs::component::TextureComponent*> cached_texture_component = std::nullopt;
};

class ShaderEditor : public ecs::ISystem {

public:

	ShaderEditor(Ref<shader_manager::IShaderManager> shader_manager)
		: shader_manager_(shader_manager) {}

	void Update(float dt) override {
		for (auto const& entity : this->entities_) {
			auto maybe_text_area = this->world->GetComponentForEntity<ui::component::TextAreaComponent>(entity);
			if (maybe_text_area.has_value()) {
				auto source = maybe_text_area.value()->buffer;
				const auto pipeline = this->shader_manager_->GetAttachedPipeline();
				const auto current_source = pipeline->GetPixelShader()->GetSource();

				if (current_source == source) {
					continue;
				}

				const auto shader = this->shader_manager_->LoadShaderBySource(source, shader_manager::ShaderType::kPixel);
				if (shader) {
					auto new_pipeline = this->shader_manager_->CreateShaderPipeline();
					this->shader_manager_->AttachShader(pipeline->GetVertexShader(), new_pipeline);
					this->shader_manager_->AttachShader(shader, new_pipeline);
					this->shader_manager_->LinkPipeline(new_pipeline);
					this->shader_manager_->AttachPipeline(new_pipeline);

					this->shader_manager_->DeleteShader(pipeline->GetPixelShader());
					this->shader_manager_->DeletePipeline(pipeline);
				}
			}
		}
	}

private:
	Ref<shader_manager::IShaderManager> shader_manager_;
};

class PlayerApplication : public Application {
public:
	~PlayerApplication() {

	}

	virtual void OnInit() override {

		world->AddSystem<ui::component::TextAreaComponent>(new ShaderEditor(this->shader_manager));
		world->AddSystem<ecs::component::TransformComponent>(new ViewportControls);

		this->resource_manager_3d->Load(
			"..\\easy-engine-core\\res\\sylvanas\\sylvanas.fbx",
			easy_engine::resource_manager::DEFAULT
		).then([=](resource_manager::LoadFuture future_resource_collection) mutable {
			ecs::component::TransformComponent transform_component;
			transform_component.Scale(0.1, 0.1, 0.1);
			transform_component.Translation(0, 0, -12);
			auto entity = this->world->CreateEntity();

			auto resource_collection = future_resource_collection.get();

			ecs::component::MeshComponent mesh_component;
			ecs::component::TextureComponent texture_component;
			ecs::component::MaterialComponent material_component;

			mesh_component.sub_meshes = new std::vector<resource::Mesh*>(resource_collection.meshes);
			texture_component.textures = new std::vector<resource::Texture*>(resource_collection.textures);
			material_component.materials = new std::vector<resource::Material*>(resource_collection.materials);

			this->world->AddComponent<ecs::component::MeshComponent>(entity, mesh_component);
			this->world->AddComponent<ecs::component::TextureComponent>(entity, texture_component);
			this->world->AddComponent<ecs::component::MaterialComponent>(entity, material_component);
			this->world->AddComponent<ecs::component::TransformComponent>(entity, transform_component);
		});


		auto point_light = new resource::PointLight();
		point_light->strength = 5.f;
		ecs::component::LightComponent point_light_component(point_light);

		ecs::component::TransformComponent point_light_transform;
		point_light_transform.Translation(0.f, 1.f, 5.f);

		auto lamp_entity = this->world->CreateEntity();
		this->world->AddComponent<ecs::component::LightComponent>(lamp_entity, point_light_component);
		this->world->AddComponent<ecs::component::TransformComponent>(lamp_entity, point_light_transform);
		
		auto sun = new resource::DirectionalLight();
		sun->strength = 5.f;
		ecs::component::LightComponent sun_component(sun);

		ecs::component::TransformComponent sun_transform;
		sun_transform.Translation(0.f, 1.f, 5.f);

		auto sun_entity = this->world->CreateEntity();
		this->world->AddComponent<ecs::component::LightComponent>(sun_entity, sun_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sun_entity, sun_transform);

		this->SetupWindow();
	}

	void SetupWindow() {
		auto shader_editor_window = world->CreateEntity();
		auto window_component = ui::component::WindowComponent();
		window_component.height = 800;
		window_component.width = 600;
		window_component.title = "Shader editor";
		ecs::component::TransformComponent shader_editor_transform_component;
		shader_editor_transform_component.Translation(100, 100, 0);

		world->AddComponent<ecs::component::TransformComponent>(shader_editor_window, shader_editor_transform_component);
		world->AddComponent<ui::component::WindowComponent>(shader_editor_window, window_component);

		auto text_area = world->CreateEntity();
		auto pixel_shader = this->shader_manager->GetAttachedPipeline()->GetPixelShader();
		auto source = pixel_shader->GetSource();
		auto text_area_component = ui::component::TextAreaComponent(800, 2000, 40000, source);
		ecs::component::TransformComponent text_area_transform_component;
		ecs::component::ParentEntityComponent window_parent_component;
		window_parent_component.entity = shader_editor_window.entity;

		world->AddComponent<ecs::component::TransformComponent>(text_area, text_area_transform_component);
		world->AddComponent<ui::component::TextAreaComponent>(text_area, text_area_component);
		world->AddComponent<ecs::component::ParentEntityComponent>(text_area, window_parent_component);
	}
};

int main() {
	PlayerApplication* application = new PlayerApplication();
	application->Run();
}