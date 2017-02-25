#pragma once

// std headers
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// External headers
#include <Eigen\Core>

// Internal headers
#include "BaseDataTypes.h"
#include "ResourceManager.h"
#include "Renderable3D.h"

#ifndef RESOURCE_MANAGER_3D_H
namespace easy_engine {
	namespace resource_manager {
		class ResourceManager3D : public ResourceManager {
		public:
			ResourceManager3D(std::string base_path);
			~ResourceManager3D();

			renderable::Renderable3D* LoadObj(std::string path_relative_to_base);
		};
	}
}
#endif // !RESOURCE_MANAGER_3D_H