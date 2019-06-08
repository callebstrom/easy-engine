#include <EasyEngine/eepch.h>
#include <EasyEngine/ecs/component/TransformComponent.h>

namespace easy_engine {
	namespace ecs {
		namespace component {
			void TransformComponent::TranslationAdd(float x, float y, float z) {
				this->Translation(
					this->translation_.x() + x,
					this->translation_.y() + y,
					this->translation_.z() + z
				);
			}

			void TransformComponent::Translation(float x, float y, float z) {
				this->prev_translation_ = this->translation_;
				this->translation_ = Eigen::Translation3f(x, y, z);
			}

			void TransformComponent::RotationAdd(float radians, float pivot_x, float pivot_y, float pivot_z) {
				return this->Rotation(
					this->rotation.angle() + radians,
					pivot_x,
					pivot_y,
					pivot_z
				);
			}

			void TransformComponent::RotationAdd(float radians) {
				return this->Rotation(
					this->rotation.angle() + radians,
					0,
					0,
					0
				);
			}

			void TransformComponent::Rotation(float radians, float pivot_x, float pivot_y, float pivot_z) {
				this->rotation = Eigen::AngleAxis<float>(radians, Eigen::Vector3f(pivot_x, pivot_y, pivot_z));
			}

			void TransformComponent::Scale(float x, float y, float z) {
				this->scale = Eigen::Scaling(x, y, z);
			}

			Eigen::Affine3f TransformComponent::GetCombinedAffineTransform() {
				return this->translation_* this->rotation* this->scale;
			}
		}
	}
}