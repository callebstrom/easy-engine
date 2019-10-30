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
			LightType type;

			Light()
				: diffuse_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				specular_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				ambient_color(Eigen::Vector3f(1.f, 1.f, 1.f)),
				strength(1.f) {}
		};

		struct EASY_ENGINE_API PointLight : public Light {
			float constant;
			float linear;
			float quadratic;

			PointLight()
				: constant(1.f), linear(0.22f), quadratic(0.2f) {
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