#pragma once

// std headers
#include <vector>
#include <string>
#include <fstream>

// External headers
#include <Eigen\Core>

// Internal headers
#include "BaseDataTypes.h"
#include "ResourceManager.h"
#include "IRenderable3D.h"

#ifndef RESOURCE_MANAGER_3D_H
namespace easy_engine {
	namespace resource_manager {
		class ResourceManager3D : public ResourceManager {
		public:
			ResourceManager3D(std::string base_path);
			~ResourceManager3D();

			renderable::IRenderable3D<float*>* LoadObj(std::string path_relative_to_base);
		};
	}
}
#endif // !RESOURCE_MANAGER_3D_H