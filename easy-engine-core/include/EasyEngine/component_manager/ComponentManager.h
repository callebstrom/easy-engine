#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#pragma once

#include <EasyEngine/component_manager/AbstractComponentManager.h>

namespace easy_engine {

	namespace entity {
		class Entity;
	}

	namespace component_manager {
		template <typename Component>
		class ComponentManager : public AbstractComponentManager {
		public:
			void RegisterEntity(entity::Entity& entity, Component&& component);
		protected:
			std::map<int, entity::Entity*> registered_entities_;
			std::vector<Component> registered_components_;
		};
	}
}
#endif // !COMPONENT_MANAGER_H
