#ifndef WORLD_H
#define WORLD_H
#pragma once

#include <EasyEngine/ecs/ISystem.h>
#include <EasyEngine/ecs/entity/Entity.h>
#include <EasyEngine/ecs/component_manager/ComponentManager.h>
#include <type_traits>
#include <EasyEngine/resource/Environment.h>

namespace easy_engine {

	namespace entity {
		class EntityHandle;
	}

	namespace world {

		typedef std::multimap<ecs::ISystem*, ComponentSignature>::iterator SystemComponentSignatureIterator;

		class EASY_ENGINE_API World {
		public:
			auto CreateEntity()->entity::EntityHandle;
			auto RemoveEntity(entity::Entity const& entity) -> void;
			auto Update(float dt) const -> void;

			// TODO this should handle unique_ptr
			template <typename... ComponentTypes>
			void AddSystem(ecs::ISystem* system) {
				system->RegisterWorld(this);

				if (std::find(this->systems_.begin(), this->systems_.end(), system) == this->systems_.end()) {
					this->systems_.push_back(system);
				}

				ComponentSignature component_signature;

				int _[] ={0, (component_signature[ecs::component::Component::GetComponentFamily<ComponentTypes>()] = true, 0)...};
				(void)_;

				// Associate the system with a component signature
				this->system_component_signature_map_.insert(std::pair<ecs::ISystem*, ComponentSignature>(system, component_signature));
			}

			template <typename ComponentType>
			void AddComponent(const entity::EntityHandle& entity_handle, ComponentType& component) {
				this->AddComponent(entity_handle.entity, component);
			}

			template <typename ComponentType>
			void AddComponent(entity::Entity* entity, ComponentType& component) {
				auto component_type = std::type_index(typeid(ComponentType));
				if (!this->component_managers_.count(component_type)) {
					auto component_manager = new component_manager::ComponentManager<ComponentType>();
					this->component_managers_[component_type] = reinterpret_cast<void*>(component_manager);
				}

				auto component_manager = reinterpret_cast<component_manager::ComponentManager<ComponentType>*>(this->component_managers_[component_type]);
				component_manager->RegisterEntity(entity, &component);

				auto component_family = ecs::component::Component::GetComponentFamily<ComponentType>();
				this->entity_component_signature_map_[entity][component_family] = true;

				for (auto system : this->systems_) {
					std::pair<SystemComponentSignatureIterator, SystemComponentSignatureIterator> registered_signatures = this->system_component_signature_map_.equal_range(system);

					for (SystemComponentSignatureIterator it = registered_signatures.first; it != registered_signatures.second; it++) {
						auto registered_signature = it->second;
						auto component_mask = this->entity_component_signature_map_[entity] & registered_signature;
						auto is_entity_eligable = component_mask == registered_signature;
						if (is_entity_eligable) {
							// Notify ISystem of entity that fulfills component signature
							system->RegisterEntity(entity);
						}
					}
				}
			}
			template <typename ComponentType>
			void RemoveComponent(entity::Entity const& entity) {
				auto component_type = std::type_index(typeid(ComponentType));
				component_manager::ComponentManager<ComponentType>* component_manager = reinterpret_cast<component_manager::ComponentManager<ComponentType>*>(this->component_managers_[component_type]);
				component_manager->RemoveComponentForEntity(entity);
			}

			template<typename ComponentType>
			auto GetComponentForEntity(entity::Entity* entity) -> std::optional<ComponentType*> {
				auto component_type = std::type_index(typeid(ComponentType));

				if (this->component_managers_.find(component_type) == this->component_managers_.end()) {
					return std::nullopt;
				}

				component_manager::ComponentManager<ComponentType>* component_manager = reinterpret_cast<component_manager::ComponentManager<ComponentType>*>(this->component_managers_[component_type]);
				auto component = component_manager->GetComponentForEntity(entity);
				return component == nullptr
					? std::nullopt
					: std::optional<ComponentType*>(component);
			}

			auto SetupEnvironment(const resource::Environment& environment) -> void;

		private:
			float entity_id_seq_ = 0; // Should be in EntityManager
			std::vector<entity::Entity*> entities_;
			// std::vector<std::unique_ptr<ISystem>> systems_; // World owns systems (aka *Manager classes implementing ISystem, not to be confused with component managers)
			OrderedTypeMap<void*> component_managers_; // TODO how to make this type-safe? Aka avoid void*. Dummy interface?
			std::vector<ecs::ISystem*> systems_;
			std::multimap<ecs::ISystem*, ComponentSignature> system_component_signature_map_;
			std::map<entity::Entity*, ComponentSignature> entity_component_signature_map_;
		};
	}
}

#endif // !WORLD_H

