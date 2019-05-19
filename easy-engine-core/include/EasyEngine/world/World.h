#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/ISystem.h>
#include <EasyEngine/entity/Entity.h>
#include <EasyEngine/components/IComponent.h>
#include <EasyEngine/Common.h>
#include <type_traits>

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
			void RemoveEntity(entity::Entity const& entity);
			void Update(float dt);

			template <typename ComponentType, typename... ComponentTypes>
			void AddSystem(std::unique_ptr<ISystem> system)
			{
				auto system_ = std::move(system).get();
				this->systems_.push_back(system_);

				ComponentSignature component_signature;
				component_signature[component::GetComponentFamily<ComponentType>()] = true;
				component_signature[component::GetComponentFamily<ComponentTypes...>()] = true;

				// Associate component combination with a system
				this->component_signature_system_map_[component_signature].emplace_back(system_);
			}

			template <typename ComponentType>
			void AddComponent(entity::Entity* entity, std::shared_ptr<component::IComponent> component)
			{
				auto component_type = std::type_index(typeid(ComponentType));
				if (!this->component_managers_.count(component_type)) {
					auto component_manager = new component_manager::ComponentManager();
					this->component_managers_[component_type] = component_manager;
				}
				/** TODO register entity in correct ISystem if all ComponentTypes are met for entity.
				 *  Add component to correct component manager
				 */
				component_manager::ComponentManager* component_manager = this->component_managers_[component_type];
				component_manager->RegisterEntity(entity, component);
			}
			void RemoveComponent(entity::Entity const& entity, component::IComponent component);

			template<typename ComponentType, typename... ComponentTypes>
			std::shared_ptr<ComponentType> GetComponentForEntity(entity::Entity* entity)
			{
				auto component_type = std::type_index(typeid(ComponentType));
				component_manager::ComponentManager* component_manager = this->component_managers_.at(component_type);

				return std::dynamic_pointer_cast<ComponentType, component::IComponent>(component_manager->registered_components_[component_manager->entity_id_component_index_map_[entity->id]]);
			}

		private:
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity> entities_ = std::vector<entity::Entity>();
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			OrderedTypeMap<component_manager::ComponentManager*> component_managers_;
			std::vector<ISystem*> systems_;
			std::map<ComponentSignature, std::vector<ISystem*>, ComponentSignatureComparetor> component_signature_systems_map_;
			std::map<entity::Entity*, ComponentSignature> entity_component_signature_map_;
		};
	}
}

#endif // !WORLD_H

