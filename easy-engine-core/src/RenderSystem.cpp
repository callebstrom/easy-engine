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
			ManagerLocator::event_manager->Dispatch(event_manager::Event(event_manager::EventType::_3DPreRender));

			for (auto entity : this->entities_) {
				auto mesh_component = this->world->GetComponentForEntity<ecs::component::MeshComponent>(entity);
				auto transform_component = this->world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

				event_manager::Event render_event = event_manager::Event(event_manager::EventType::_3DObjectRenderable);

				auto event_data = new _3DObjectRenderable();
				event_data->mesh_component = mesh_component;
				event_data->transform_component = transform_component;

				render_event.data = event_data;
				EE_CORE_INFO("_3DObjectRenderable event dispatched for entity ", entity->id);
				ManagerLocator::event_manager->Dispatch(render_event);
			}

			ManagerLocator::event_manager->Dispatch(event_manager::Event(event_manager::EventType::_3DPostRender));
		}
	}
}
