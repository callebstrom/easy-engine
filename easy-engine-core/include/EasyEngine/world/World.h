#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/ISystem.h>
#include <EasyEngine/entity/Entity.h>

namespace easy_engine {

	namespace component_manager {
		template<typename Component>
		class ComponentManager;
	}

	namespace entity {
		class EntityHandle;
	}

	namespace component_manager {
		class AbstractComponentManager;
	}

	namespace world {

		class EASY_ENGINE_API World {
		public:
			entity::EntityHandle CreateEntity();
			void RemoveEntity(entity::Entity const &entity);
			template<typename Component>
			void AddComponent(entity::Entity const &entity, Component component);
			void RemoveComponent(entity::Entity const &entity);
			void Update(float dt);
			void AddSystem(std::unique_ptr<ISystem> system);

			template<typename Component, typename... Args>
			OrderedTypeMap<Component> GetComponentsByType(Component component, Args... types);
		private:
			template<typename Component>
			component_manager::ComponentManager<Component>* GetComponentManager();
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			OrderedTypeMap<component_manager::AbstractComponentManager*> component_managers_;
			std::vector<ISystem*> systems_;
		};
	}
}

#endif // !WORLD_H

