#ifndef LIGHT_H
#define LIGHT_H
#pragma once

#include <Eigen/Core>

namespace easy_engine {
	namespace resource {
		enum EASY_ENGINE_API LightType {
			kPointLight = 0,
			kDirectionalLight = 1,
			kSpotLight = 2,
			kSun = 3
		};

		struct EASY_ENGINE_API Light {
			Eigen::Vector3f diffuse_color;
			Eigen::Vector3f specular_color;
			Eigen::Vector3f ambient_color;
			float strength;

			Light()
				: diffuse_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				specular_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				ambient_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				strength(1.f) {}

		protected:
			LightType type;
		};

		struct EASY_ENGINE_API PointLight : public Light {
			Eigen::Vector3f position;

			float constant;
			float linear;
			float quadratic;

			PointLight()
				: position(Eigen::Vector3f(0, 0, 0)), constant(1), linear(0.22), quadratic(0.2) {
				type = LightType::kPointLight;
			};
		};

		struct EASY_ENGINE_API DirectionalLight : public Light {
			Eigen::Vector3f direction;

			DirectionalLight() { type = LightType::kDirectionalLight; };
		};

		struct EASY_ENGINE_API SpotLight : public Light {
			Eigen::Vector3f position;
			Eigen::Vector3f direction;

			float cutoff;

			SpotLight() { type = LightType::kSpotLight; };
		};
	}
}

#endif LIGHT_H