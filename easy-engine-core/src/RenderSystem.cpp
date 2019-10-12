#include <EasyEngine/eepch.h>
#include <EasyEngine/render_manager/RenderSystem.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/event_manager/Event.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TextureComponent.h>
#include <EasyEngine/ecs/component/MaterialComponent.h>
#include <EasyEngine/render_manager/_3DObjectRenderable.h>

namespace easy_engine {
	namespace render_manager {

		struct RenderSystem::Impl {

			Impl(std::shared_ptr<event_manager::EventManager> event_manager)
				: event_manager(event_manager) {}

			std::deque<event_manager::Event> buffered_object_renderable_events;
			std::shared_ptr<event_manager::EventManager> event_manager;
		};

		RenderSystem::RenderSystem(std::shared_ptr<event_manager::EventManager> event_manager)
			: p_impl_(new Impl(event_manager)) {
			this->p_impl_->event_manager->Subscribe(event_manager::EventType::kRender, this);
		}

		void RenderSystem::Update(float dt) {
			for (auto entity : this->entities_) {
				auto maybe_mesh_component = this->world->GetComponentForEntity<ecs::component::MeshComponent>(entity);
				auto maybe_transform_component = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);
				auto maybe_texture_component = this->world->GetComponentForEntity<ecs::component::TextureComponent>(entity);
				auto maybe_material_component = this->world->GetComponentForEntity<ecs::component::MaterialComponent>(entity);

				event_manager::Event render_event = event_manager::Event(event_manager::EventType::k3DObjectRenderable);

				auto event_data = new _3DObjectRenderable();

				if (!maybe_mesh_component.has_value() || !maybe_transform_component.has_value()) continue;

				event_data->mesh_component = maybe_mesh_component.value();
				event_data->transform_component = maybe_transform_component.value();

				if (maybe_texture_component.has_value()) {
					event_data->texture_component = maybe_texture_component;
					event_data->has_textures = maybe_texture_component.value()->textures->size() > 0;
				}

				if (maybe_material_component.has_value()) {
					event_data->material_component = maybe_material_component;
					event_data->has_materials = maybe_material_component.value()->materials->size() > 0;
				}

				render_event.data = event_data;
				this->p_impl_->buffered_object_renderable_events.push_back(render_event);
			}
		}
		auto RenderSystem::OnEvent(event_manager::Event event) -> void {
			switch (event.event_type) {
			case event_manager::EventType::kRender:
				while (!this->p_impl_->buffered_object_renderable_events.empty()) {
					this->p_impl_->event_manager->Dispatch(this->p_impl_->buffered_object_renderable_events.front());
					this->p_impl_->buffered_object_renderable_events.pop_front();
				}
				break;
			}
		}
	}
}
