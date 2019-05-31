#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <Eigen/Geometry>

namespace easy_engine {
	namespace ecs {
		namespace component {
			class TransformComponent : public Component {
			public:

				TransformComponent* TranslationAdd(float x, float y, float z)
				{
					return this->Translation(
						this->translation_.x() + x,
						this->translation_.y() + y,
						this->translation_.z() + z
					);
				}

				TransformComponent* Translation(float x, float y, float z)
				{
					this->prev_translation_ = this->translation_;
					this->translation_ = Eigen::Translation3f(x, y, z);
					return this;
				}

				TransformComponent* RotationAdd(float radians, float pivot_x = 0, float pivot_y = 0, float pivot_z = 0)
				{
					return this->Rotation(this->rotation.angle() + radians, pivot_x, pivot_y, pivot_z);
				}

				TransformComponent* Rotation(float radians, float pivot_x = 0, float pivot_y = 0, float pivot_z = 0) // Default pivot is origin
				{
					this->rotation = Eigen::AngleAxis<float>(radians, Eigen::Vector3f(pivot_x, pivot_y, pivot_z));
					return this;
				}

				TransformComponent* Scale(float x, float y, float z)
				{
					this->scale = Eigen::Scaling(x, y, z);
					return this;
				}

				Eigen::Affine3f GetCombinedAffineTransform()
				{
					return this->translation_* this->rotation* this->scale;
				}

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

