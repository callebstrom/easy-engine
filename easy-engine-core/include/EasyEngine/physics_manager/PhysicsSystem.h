#pragma once

#include <EasyEngine/ecs/ISystem.h>
#include <EasyEngine/physics_manager/PhysicsManager.h>

namespace easy_engine {
	namespace physics_manager {

		class EASY_ENGINE_API PhysicsSystem : public ecs::ISystem {
		public:
			PhysicsSystem(Ref<PhysicsManager> event_manager);
			void Update(float dt) override;
		private:
			std::shared_ptr<PhysicsManager> physics_manager_;
		};
	}
}
