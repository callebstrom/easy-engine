#ifndef I_SYSTEM_H
#define I_SYSTEM_H
#pragma once

#include <EasyEngine/ecs/entity/Entity.h>
#include <EasyEngine/Common.h>

namespace easy_engine {

	namespace world {
		class World;
	}

	namespace ecs {
		class EASY_ENGINE_API ISystem {
		public:
			ISystem() = default;
			~ISystem() = default;
			ISystem(const ISystem&) = delete;
			ISystem& operator=(const ISystem&) = delete;
			ISystem(ISystem&&) = default;
			ISystem& operator=(ISystem&&) = default;

			virtual void Update(float dt) = 0;
			void RegisterWorld(world::World* world) {
				this->world = world;
			}

			void RegisterEntity(entity::Entity* entity) {
				this->entities_.insert(entity);
			}

		protected:
			std::set<entity::Entity*> entities_;
			world::World* world;
		};
	}
}

#endif // !I_SYSTEM_H

