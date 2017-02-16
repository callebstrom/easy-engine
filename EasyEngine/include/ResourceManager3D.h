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

#ifndef THREED_RESOURCE_MANAGER_H
namespace easy_engine {
	namespace resource_manager {
		class ResourceManager3D : public ResourceManager {
		public:
			ResourceManager3D(std::string base_path);
			~ResourceManager3D();
			obj_vector* LoadObj(std::string path_relative_to_base);
		};
	}
}
#endif // !THREED_RESOURCE_MANAGER_H