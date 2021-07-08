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
				this->previous_translation_ = this->translation_;
				this->translation_ = Eigen::Translation3f(x, y, z);
			}

			void TransformComponent::RotationAdd(float radians, const Pivot pivot) {
				this->rotation_ = this->rotation_ * Eigen::AngleAxis<float>(radians, Eigen::Vector3f(pivot));
			}

			void TransformComponent::Rotation(float radians, const Pivot pivot) {
				this->rotation_ = Eigen::AngleAxis(radians, Eigen::Vector3f(pivot));
			}

			void TransformComponent::Scale(float x, float y, float z) {
				this->scale_ = Eigen::Scaling(x, y, z);
			}
			
			void TransformComponent::ScaleMultiply(float x, float y, float z) {
				auto const prev = this->scale_.diagonal();
				this->scale_ = Eigen::Scaling(prev.x() * x, prev.y() * y, prev.z() * z);
			}
		}
	}
}