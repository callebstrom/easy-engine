#include <EasyEngine/eepch.h>
#include <EasyEngine/ecs/entity/EntityHandle.h>
#include <EasyEngine/world/World.h>

namespace easy_engine {
	namespace entity {
		void EntityHandle::destroy() {
			this->world->RemoveEntity(*entity);
		}

		template<typename ComponentType>
		void EntityHandle::AddComponent(ComponentType c) {
			this->world->AddComponent(*entity, c);
		}

		template<typename ComponentType>
		void EntityHandle::RemoveComponent() {
			this->world->RemoveComponent<ComponentType>(*entity);
		}
	}
}