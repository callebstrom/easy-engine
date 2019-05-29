#include <EasyEngine/eepch.h>
#include <EasyEngine/render_manager/RenderSystem.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/event_manager/Event.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/render_manager/_3DObjectRenderable.h>

namespace easy_engine {
	namespace render_manager {
		RenderSystem::RenderSystem()
		{
		}

		void RenderSystem::Update(float dt)
		{
			for (auto entity : this->entities_) {
				auto mesh_component = this->world->GetComponentForEntity<ecs::component::MeshComponent>(entity);
				auto transform_component = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

				event_manager::Event render_event = event_manager::Event();

				auto event_data = new _3DObjectRenderable();
				event_data->mesh_component = mesh_component;
				event_data->transform_component = transform_component;

				render_event.data = event_data;
				render_event.event_type = event_manager::EventType::_3DObjectRenderable;
				render_event.message_id = atoi(mesh_component->mesh->name.c_str());
				EE_CORE_INFO("_3DObjectRenderable event dispatched for entity ", entity->id);
				ManagerLocator::event_manager->Dispatch(render_event);
			}

			event_manager::Event post_render_event = event_manager::Event();
			post_render_event.event_type = event_manager::EventType::_3DPostRender;
			ManagerLocator::event_manager->Dispatch(post_render_event);
		}
	}
}
