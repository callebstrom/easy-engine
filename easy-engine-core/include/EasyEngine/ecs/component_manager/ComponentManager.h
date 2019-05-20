#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/Common.h>

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

			void RegisterEntity(entity::Entity* entity, std::shared_ptr<component::Component> component);
		protected:
			friend class world::World;
			// Maps entity id to component index
			std::map<float, int> entity_id_component_index_map_;
			// Holds all components of the type associated with a given ComponentManager
			std::vector<std::shared_ptr<component::Component>> registered_components_;
		};
	}
}
#endif // !COMPONENT_MANAGER_H
