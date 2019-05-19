#ifndef I_SYSTEM_H
#define I_SYSTEM_H
#pragma once

#include <EasyEngine/entity/Entity.h>
#include <EasyEngine/Common.h>

namespace easy_engine {

	namespace world {
		class World;
	}

	class EASY_ENGINE_API ISystem {
	public:
		ISystem() = default;
		~ISystem() = default;
		ISystem(const ISystem&) = delete;
		ISystem& operator=(const ISystem&) = delete;
		ISystem(ISystem&&) = default;
		ISystem& operator=(ISystem&&) = default;

		virtual void Update(float dt) = 0;
		void RegisterWorld(world::World* world)
		{
			this->world = world;
		}

		void RegisterEntity(entity::Entity* entity)
		{
			this->entities_.push_back(entity);
		}

	protected:
		std::vector<entity::Entity*> entities_ = std::vector<entity::Entity*>();
		world::World* world;
	};
}

#endif // !I_SYSTEM_H

