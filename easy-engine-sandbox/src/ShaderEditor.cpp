#include <EasyEngine/eepch.h>

#include <EasyEngine/EasyEngine.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/ManagerLocator.h>

using namespace easy_engine;

using input_manager::Key;
using input_manager::Action;
using input_manager::Modifier;

class PlayerSystem : public ecs::ISystem, public event_manager::IObserver {
public:
	PlayerSystem() {
		ManagerLocator::event_manager->Subscribe(
			event_manager::EventType::kKeyboard,
			this
		);
	}

	auto OnEvent(event_manager::Event event_) -> void override {
		event_buffer_.push_back(event_);
		// auto event = reinterpret_cast<input_manager::KeyboardEvent*>(event_.data);
		/*if (event->action == Action::kReleased && event->key == Key::kT) {
			this->textures = !this->textures;
			for (auto entity : this->entities_) {
				if (!this->textures) {
					if (!this->cached_texture_component.has_value()) {
						EE_TRACE("Caching textures");
						this->cached_texture_component = this->world->GetComponentForEntity<ecs::component::TextureComponent>(entity);
					}
					EE_TRACE("Removing textures");
					this->world->RemoveComponent<ecs::component::TextureComponent>(*entity);
				}
				else if (this->cached_texture_component.has_value()) {
					EE_TRACE("Re-adding cached texture");
					this->world->AddComponent<ecs::component::TextureComponent>(entity, *cached_texture_component.value());
				}
			}
		}*/
	}

	auto Update(float dt) -> void override {
		for (auto event_ : this->event_buffer_) {
			auto event = reinterpret_cast<input_manager::KeyboardEvent*>(event_.data);
			if (event->action == Action::kPressed) {
				for (auto entity : this->entities_) {
					auto maybe_transform = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					if (!maybe_transform.has_value()) continue;

					auto transform = maybe_transform.value();

					switch (event->key) {
					case Key::kW:
						transform->TranslationAdd(0, 0, -0.01 * dt);
						break;
					case Key::kS:
						transform->TranslationAdd(0, 0, 0.01 * dt);
						break;
					case Key::kA:
						transform->TranslationAdd(-0.01 * dt, 0, 0);
						break;
					case Key::kD:
						transform->TranslationAdd(0.01 * dt, 0, 0);
						break;
					case Key::kR:
						auto rotation_direction = event->modifiers == Modifier::kControl ? -1 : 1;
						transform->RotationAdd(rotation_direction * 0.01 * dt);
						break;
					}
				}
			}
		}

		// Clear buffer after processing all events
		event_buffer_.clear();
	}
private:
	std::vector<event_manager::Event> event_buffer_;
	bool textures = true;
	std::optional<ecs::component::TextureComponent*> cached_texture_component = std::nullopt;
};

class PlayerApplication : public Application {
public:
	~PlayerApplication() {

	}

	virtual void OnInit() override {

		world->AddSystem<ecs::component::MeshComponent, ecs::component::TransformComponent>(new PlayerSystem);

		ecs::component::MeshComponent mesh_component;
		ecs::component::TextureComponent texture_component;
		ecs::component::MaterialComponent material_component;
		this->resource_manager_3d->Load("..\\easy-engine-core\\res\\sylvanas\\sylvanas.fbx", mesh_component, texture_component, material_component);

		ecs::component::TransformComponent transform_component;
		transform_component.Scale(0.05, 0.05, 0.05);
		transform_component.TranslationAdd(0, -8, -15);
		// transform_component.RotationAdd(-1.500796f, 1, 0, 0);
		auto sylvana = this->world->CreateEntity();

		this->world->AddComponent<ecs::component::MeshComponent>(sylvana, mesh_component);
		this->world->AddComponent<ecs::component::TextureComponent>(sylvana, texture_component);
		this->world->AddComponent<ecs::component::MaterialComponent>(sylvana, material_component);
		this->world->AddComponent<ecs::component::TransformComponent>(sylvana, transform_component);

		resource::Environment environment;
		resource::PointLight point_light;
		point_light.position = Eigen::Vector3f(0.f, 1.f, 5.f);
		point_light.strength = 50.f;

		resource::DirectionalLight directional_light;
		directional_light.direction = Eigen::Vector3f(1.f, 1.f, 1.f);
		directional_light.strength = 1.f;

		environment.AddLight(point_light);
		// environment.AddLight(directional_light);

		world->SetupEnvironment(environment);

		auto shader_editor = world->CreateEntity();
		auto shader_editor_window = ui::component::WindowComponent();
		shader_editor_window.height = 230;
		shader_editor_window.width = 250;
		shader_editor_window.title = "Shader editor";
		ecs::component::TransformComponent shader_editor_transform_component;

		world->AddComponent<ecs::component::TransformComponent>(shader_editor, shader_editor_transform_component);
		world->AddComponent<ui::component::WindowComponent>(shader_editor, shader_editor_window);
	}
};

int main() {
	PlayerApplication* application = new PlayerApplication();
	application->Run();
	// std::this_thread::sleep_for(std::chrono::seconds(30));
	// application->Close();
}