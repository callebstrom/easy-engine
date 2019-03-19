#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/component_manager/IComponentManager.h>
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

		private:
			template<typename ComponentType>
			component_manager::IComponentManager<ComponentType>* GetComponentManager();
			float entity_id_seq_ = 0;
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
		};
	}
}

#endif // !WORLD_H

