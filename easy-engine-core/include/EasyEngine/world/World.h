#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/ISystem.h>
#include <EasyEngine/entity/Entity.h>
#include <EasyEngine/components/IComponent.h>

namespace easy_engine {

	namespace component_manager {
		class ComponentManager;
	}

	namespace entity {
		class EntityHandle;
	}

	namespace world {

		class EASY_ENGINE_API World { 
		public:
			entity::EntityHandle CreateEntity();
			void RemoveEntity(entity::Entity const &entity);
			void Update(float dt);
			void AddSystem(std::unique_ptr<ISystem> system);

			template <typename ComponentType>
			void AddComponentManager(std::unique_ptr<component_manager::ComponentManager> component_manager) {
				auto test = std::type_index(typeid(ComponentType));
				this->component_managers_[typeid(ComponentType)] = std::move(component_manager).get();
			}

			template <typename ComponentType>
			void AddComponent(entity::Entity* entity, std::unique_ptr<component::IComponent> component)
			{
				/** TODO register entity in correct ISystem if all ComponentTypes are met for entity.
				 *  Add component to correct component manager
				 */
				auto test = std::type_index(typeid(ComponentType));
				component_manager::ComponentManager* component_manager = this->component_managers_[typeid(ComponentType)];
				component_manager->RegisterEntity(entity, std::move(component));
			}
			void RemoveComponent(entity::Entity const& entity, component::IComponent component);

			template<typename Component, typename ...Args>
			OrderedTypeMap<Component> GetComponentsByType(Component component, Args ...types)
			{
				static auto const& orderedTypeMap = new OrderedTypeMap<Component>();
			}
		private:
			template<typename ComponentType, typename std::enable_if<std::is_base_of<component::IComponent, ComponentType>::value>::type* = nullptr>
			component_manager::ComponentManager* GetComponentManager();
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			OrderedTypeMap<component_manager::ComponentManager*> component_managers_;
			std::vector<ISystem*> systems_;
		};
	}
}

#endif // !WORLD_H

