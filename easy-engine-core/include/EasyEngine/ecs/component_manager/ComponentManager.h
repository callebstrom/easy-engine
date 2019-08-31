#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/Common.h>
#include <EasyEngine/memory/LinearAllocator.h>

namespace easy_engine {

	namespace entity {
		class Entity;
	}

	namespace component_manager {
		template <typename ComponentType>
		class ComponentManager {

		public:
			ComponentManager() = default;
			virtual ~ComponentManager() = default;
			ComponentManager(const ComponentManager&) = default;
			ComponentManager& operator=(const ComponentManager&) = default;
			ComponentManager(ComponentManager&&) = default;
			ComponentManager& operator=(ComponentManager&&) = default;

			void RegisterEntity(entity::Entity* entity, ComponentType* component) {
				this->entity_id_component_offset_map_[entity->id] = this->allocator.Allocate(component);
			}

			auto GetComponentForEntity(entity::Entity* entity) -> ComponentType* {
				if (this->entity_id_component_offset_map_.find(entity->id) == this->entity_id_component_offset_map_.end()) {
					return nullptr;
				}

				return this->allocator.buffer + this->entity_id_component_offset_map_[entity->id];
			}

			auto RemoveComponentForEntity(const entity::Entity& entity) -> void {
				if (this->entity_id_component_offset_map_.find(entity.id) == this->entity_id_component_offset_map_.end()) return;

				this->entity_id_component_offset_map_.erase(entity.id);
				// TODO should also remove component data from allocator
			}

		protected:
			// Maps entity id to component index
			std::map<float, size_t> entity_id_component_offset_map_;
			// Holds all components of the type associated with a given ComponentManager in linear memory
			memory::LinearAllocator<ComponentType> allocator;
		};
	}
}
#endif // !COMPONENT_MANAGER_H
