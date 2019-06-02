#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <Eigen/Geometry>

namespace easy_engine {

	namespace render_manager {
		class RenderManagerOpenGL;
	}

	namespace ecs {
		namespace component {
			class EASY_ENGINE_API TransformComponent : public Component {
			public:
				void TranslationAdd(float x, float y, float z);
				void Translation(float x, float y, float z);
				void RotationAdd(float radians, float pivot_x = 0, float pivot_y = 0, float pivot_z = 0);
				void Rotation(float radians, float pivot_x = 0, float pivot_y = 0, float pivot_z = 0);
				void Scale(float x, float y, float z);

				Eigen::Affine3f GetCombinedAffineTransform();

			private:
				friend class render_manager::RenderManagerOpenGL;
				Eigen::Translation3f translation_ = Eigen::Translation3f(0.f, 0.f, 0.f);
				Eigen::Translation3f prev_translation_ = Eigen::Translation3f(0.f, 0.f, 0.f);
				Eigen::AngleAxis<float> rotation = Eigen::AngleAxis<float>(0.f, Eigen::Vector3f(0, 0, 0));
				Eigen::AlignedScaling3f scale = Eigen::Scaling(1.f, 1.f, 1.f);
			};
		}
	}
}

#endif // !TRANSFORM_COMPONENT_H

