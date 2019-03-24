#include <EasyEngine/eepch.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/entity/EntityHandle.h>
#include <EasyEngine/entity/Entity.h>

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

		void World::RemoveEntity(entity::Entity const &entity)
		{
		}
		void World::RemoveComponent(entity::Entity const &entity)
		{
		}

		template<typename Component>
		void World::AddComponent(entity::Entity const &entity, Component component)
		{
			/** TODO register entity in correct ISystem if all ComponentTypes are met for entity.
			 *  Add component to correct component manager
			 */

			this->component_managers_[std::type_index(typeid(component))] = component;
			return nullptr_t;
		}

		template<typename Component, typename ...Args>
		OrderedTypeMap<Component> World::GetComponentsByType(Component component, Args ...types)
		{
			static auto const& orderedTypeMap = new OrderedTypeMap<Component>();
		
		}

		template<typename ComponentType>
		component_manager::ComponentManager<ComponentType>* World::GetComponentManager()
		{
			return nullptr_t;
		}

		void World::Update(float dt)
		{

		}

		void World::AddSystem(std::unique_ptr<ISystem> system)
		{
			this->systems_.push_back(std::move(system).get());
		};
	}

}
