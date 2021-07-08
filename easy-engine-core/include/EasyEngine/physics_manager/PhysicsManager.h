#pragma once

#include <EasyEngine/ecs/component/RigidBodyComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <Eigen/Geometry>
#include <EasyEngine/Common.h>

namespace easy_engine {
	namespace physics_manager {

		class EASY_ENGINE_API PhysicsManager {
		public:
			PhysicsManager();
			auto Register(Ref<ecs::component::RigidBodyComponent> rigid_body_component, Ref<ecs::component::TransformComponent> transform_component) -> void;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

