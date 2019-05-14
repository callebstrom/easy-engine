#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#pragma once

#include <EasyEngine/components/IComponent.h>

namespace easy_engine {

	namespace entity {
		class Entity;
	}

	namespace world {
		class World;
	}

	namespace component_manager {
		class EASY_ENGINE_API ComponentManager {

		public:
			ComponentManager() = default;
			virtual ~ComponentManager() = default;
			ComponentManager(const ComponentManager&) = default;
			ComponentManager& operator=(const ComponentManager&) = default;
			ComponentManager(ComponentManager&&) = default;
			ComponentManager& operator=(ComponentManager&&) = default;

			void RegisterEntity(entity::Entity* entity, std::unique_ptr<component::IComponent> component);
		protected:
			friend class world::World;
			// Maps component index with a given entity
			std::map<int, entity::Entity*> registered_entities_;
			// Holds all components of the type associated with a given ComponentManager
			std::vector<component::IComponent*> registered_components_;
		};
	}
}
#endif // !COMPONENT_MANAGER_H
