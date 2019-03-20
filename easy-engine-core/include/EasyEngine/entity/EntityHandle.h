#ifndef ENTITY_HANDLE_H
#define ENTITY_HANDLE_H
#pragma once

#include <EasyEngine/world/World.h>

namespace easy_engine {
	namespace entity {

		class Entity;

		class EASY_ENGINE_API EntityHandle {

		public:

			Entity* entity;
			world::World* world;

			void destroy() {
				this->world->RemoveEntity(entity);
			}

			template<typename ComponentType>
			void AddComponent(ComponentType c) {
				this->world->AddComponent(entity, c);
			}

			template<typename ComponentType>
			void RemoveComponent() {
				this->world->RemoveComponent<ComponentType>(entity);
			}

			
		};
	}
}

#endif // !ENTITY_HANDLE_H
