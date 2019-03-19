#include <EasyEngine/eepch.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/entity/EntityHandle.h>

namespace easy_engine {
	namespace world {
		entity::EntityHandle World::CreateEntity() {
			entity::Entity entity = entity::Entity(this->entity_id_seq_++);
			this->entities_.push_back(entity);
			entity::EntityHandle entity_handle = entity::EntityHandle();
			entity_handle.entity = &entity;
			entity_handle.world = (world::World*)(this);
			return entity_handle;
		}

		void World::RemoveEntity(entity::Entity * entity)
		{
		}
		void World::RemoveComponent(entity::Entity * entity)
		{
		}

		template<typename Component>
		void World::AddComponent(entity::Entity* entity, Component component) {
			return nullptr_t;
		}

		template<typename ComponentType>
		component_manager::IComponentManager<ComponentType>* World::GetComponentManager()
		{
			return nullptr_t;
		}
	}

}
