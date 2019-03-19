#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/component_manager/ComponentManager.h>
#include <EasyEngine/component_manager/AbstractComponentManager.h>
#include <EasyEngine/entity/Entity.h>

namespace easy_engine {

	namespace entity {
		class EntityHandle;
	}

	namespace world {
		
		class World {
		public:
			entity::EntityHandle CreateEntity();
			void RemoveEntity(entity::Entity* entity);
			template<typename Component>
			void AddComponent(entity::Entity* entity, Component component);
			void RemoveComponent(entity::Entity* entity);
			void Update(float dt);
		private:
			template<typename Component>
			component_manager::ComponentManager<Component>* GetComponentManager();
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
			// std::vector<ISystem*> systems_;
			std::vector<component_manager::AbstractComponentManager*> component_managers_;
		};
	}
}

#endif // !WORLD_H

