#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once

#include <Eigen/Core>

namespace easy_engine {
	namespace resource {
		class EASY_ENGINE_API Material {

		public:
			float shininess;
			Eigen::Vector3f diffuse_color;
			Eigen::Vector3f specular_color;
			Eigen::Vector3f emmisive_color;

			size_t diffuse_texture_index;
			size_t specular_texture_index;
			size_t emissive_texture_index;

			Material();
		};
	}
}
#endif // !MATERIAL_H