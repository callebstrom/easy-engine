#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/resource/Mesh.h>
#include <EasyEngine/Common.h>
#include <Eigen/Core>

namespace easy_engine {
	namespace ecs {
		namespace component {
			class EASY_ENGINE_API RigidBodyComponent : public Component {
			public:
				Eigen::Vector3f	collision_vector;
				float mass;
				Scope<resource::Mesh> collision_shape;

			};
		}
	}
}
