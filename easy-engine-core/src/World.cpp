#include <EasyEngine/eepch.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/ecs/entity/EntityHandle.h>
#include <EasyEngine/ecs/entity/Entity.h>
#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/ecs/component_manager/ComponentManager.h>

namespace easy_engine {
	namespace world {
		entity::EntityHandle World::CreateEntity()
		{
			entity::Entity* entity = new entity::Entity(this->entity_id_seq_++);
			this->entities_.push_back(entity);
			entity::EntityHandle entity_handle = entity::EntityHandle();
			entity_handle.entity = entity;
			entity_handle.world = this;
			return entity_handle;
		}

		void World::RemoveEntity(entity::Entity const& entity)
		{
		}

		void World::Update(float dt)
		{
			for (auto system : this->systems_) {
				system->Update(dt);
			}

		}

		void World::RemoveComponent(entity::Entity const& entity, ecs::component::Component component)
		{

		}

	}

}
