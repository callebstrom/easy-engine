#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/component_manager/ComponentManager.h>
#include <EasyEngine/component_manager/AbstractComponentManager.h>
#include <EasyEngine/entity/Entity.h>
#include <EasyEngine/ISystem.h>

namespace easy_engine {

	namespace entity {
		class EntityHandle;
	}

	namespace world {

		class EASY_ENGINE_API World {
		public:
			entity::EntityHandle CreateEntity();
			void RemoveEntity(entity::Entity* entity);
			template<typename Component>
			void AddComponent(entity::Entity* entity, Component component);
			void RemoveComponent(entity::Entity* entity);
			void Update(float dt);

			template<typename Component, typename... Args>
			OrderedTypeMap<Component> GetComponentsByType(Component component, Args... types);
		private:
			template<typename Component>
			component_manager::ComponentManager<Component>* GetComponentManager();
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			std::vector<component_manager::AbstractComponentManager*> component_managers_;
		};
	}
}

#endif // !WORLD_H

