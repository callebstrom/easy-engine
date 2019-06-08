#include <EasyEngine/eepch.h>
#include <EasyEngine/resource/Material.h>

namespace easy_engine {
	namespace resource {
		Material::Material()
			: shininess(1.f),
			specular_color(Eigen::Vector3f(1, 1, 1)),
			diffuse_color(Eigen::Vector3f(1, 1, 1))
		{}
	}
}