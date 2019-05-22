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

			void RegisterEntity(entity::Entity* entity, ComponentType* component)
			{
				this->entity_id_component_offset_map_[entity->id] = this->allocator.Allocate(component);
			}

			ComponentType* GetComponentForEntity(entity::Entity* entity)
			{
				return this->allocator.buffer + this->entity_id_component_offset_map_[entity->id];
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
