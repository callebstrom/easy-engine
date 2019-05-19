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

			// TODO this should handle unique_ptr
			template <typename ComponentType, typename... ComponentTypes>
			void AddSystem(std::unique_ptr<ISystem> system_)
			{
				auto system = std::move(system_).get();
				system->RegisterWorld(this);
				this->systems_.push_back(system);

				ComponentSignature component_signature;
				component_signature[component::GetComponentFamily<ComponentType>()] = true;
				component_signature[component::GetComponentFamily<ComponentTypes...>()] = true;

				// Associate the system with a component signature
				this->system_component_signature_map_[system] = component_signature;
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

				this->entity_component_signature_map_[entity][component::GetComponentFamily<ComponentType>()] = true;

				for (auto system : this->systems_) {
					auto component_mask = this->entity_component_signature_map_[entity] &= this->system_component_signature_map_[system];
					auto is_entity_eligable = component_mask == this->system_component_signature_map_[system];
					if (is_entity_eligable) {
						// Notify ISystem of entity that fulfills component signature
						system->RegisterEntity(entity);
					}
				}
			}
			void RemoveComponent(entity::Entity const& entity, component::IComponent component);

			template<typename ComponentType>
			std::shared_ptr<ComponentType> GetComponentForEntity(entity::Entity* entity)
			{
				auto component_type = std::type_index(typeid(ComponentType));
				component_manager::ComponentManager* component_manager = this->component_managers_[component_type];

				return std::dynamic_pointer_cast<ComponentType, component::IComponent>(component_manager->registered_components_[component_manager->entity_id_component_index_map_[entity->id]]);
			}

		private:
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity*> entities_;
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			OrderedTypeMap<component_manager::ComponentManager*> component_managers_;
			std::vector<ISystem*> systems_;
			std::map<ISystem*, ComponentSignature> system_component_signature_map_;
			std::map<entity::Entity*, ComponentSignature> entity_component_signature_map_;
		};
	}
}

#endif // !WORLD_H

