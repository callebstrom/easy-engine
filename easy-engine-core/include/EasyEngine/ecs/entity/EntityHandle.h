#ifndef ENTITY_HANDLE_H
#define ENTITY_HANDLE_H
#pragma once

namespace easy_engine {

	namespace world {
		class World;
	}

	namespace entity {

		class Entity;

		class EASY_ENGINE_API EntityHandle {

		public:

			Entity* entity;
			world::World* world;

			void destroy();

			template<typename ComponentType>
			void AddComponent(ComponentType c);

			template<typename ComponentType>
			void RemoveComponent();


		};
	}
}

#endif // !ENTITY_HANDLE_H
