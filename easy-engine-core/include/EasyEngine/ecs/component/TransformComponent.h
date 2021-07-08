#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <Eigen/Geometry>

namespace easy_engine {

	namespace render_manager {
		class RenderManagerOpenGL;
		class RenderSystem;
	}

	namespace ecs {
		namespace component {
			using Pivot = float[3];

			constexpr Pivot kPivotX ={1, 0, 0};
			constexpr Pivot kPivotY ={0, 1, 0};
			constexpr Pivot kPivotZ ={0, 0, 0};

			class EASY_ENGINE_API TransformComponent : public Component {
			public:
				void TranslationAdd(float x, float y, float z);
				void Translation(float x, float y, float z);
				void RotationAdd(float radians, const Pivot pivot);
				void Rotation(float radians, const Pivot pivot);
				void Scale(float x, float y, float z);
				void ScaleMultiply(float x, float y, float z);

				auto GetCombinedAffineTransform() const -> Eigen::Affine3f;
				auto GetTranslation() const -> Eigen::Translation3f { return this->translation_; }
				auto GetPreviousTranslation() const -> Eigen::Translation3f { return this->previous_translation_; }
				auto GetRotation() const -> Eigen::AngleAxis<float> { return this->rotation_; }
				auto GetScale() const -> Eigen::AlignedScaling3f { return this->scale_; }

			private:
				Eigen::Translation3f translation_ = Eigen::Translation3f(0.f, 0.f, 0.f);
				Eigen::Translation3f previous_translation_ = Eigen::Translation3f(0.f, 0.f, 0.f);
				Eigen::AngleAxis<float> rotation_ = Eigen::AngleAxis<float>(0.f, Eigen::Vector3f(0, 0, 0));
				Eigen::AlignedScaling3f scale_ = Eigen::Scaling(1.f, 1.f, 1.f);
			};
		}
	}
}

#endif // !TRANSFORM_COMPONENT_H

