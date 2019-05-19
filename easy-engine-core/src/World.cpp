#include <EasyEngine/eepch.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/entity/EntityHandle.h>
#include <EasyEngine/entity/Entity.h>
#include <EasyEngine/components/IComponent.h>
#include <EasyEngine/component_manager/ComponentManager.h>

namespace easy_engine {
	namespace world {
		entity::EntityHandle World::CreateEntity()
		{
			entity::Entity entity = entity::Entity(this->entity_id_seq_++);
			this->entities_.push_back(entity);
			entity::EntityHandle entity_handle = entity::EntityHandle();
			entity_handle.entity = &entity;
			entity_handle.world = (world::World*)(this);
			return entity_handle;
		}

		void World::RemoveEntity(entity::Entity const& entity)
		{
		}

		void World::Update(float dt)
		{

		}

		void World::RemoveComponent(entity::Entity const& entity, component::IComponent component)
		{

		}

	}

}
