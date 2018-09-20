#ifndef RESOURCE_MANAGER_3D_H
#define RESOURCE_MANAGER_3D_H
#pragma once

// std headers
#include <fstream>
#include <sstream>

// Eigen
#include <Eigen/Core>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// Internal headers
#include <Common.h>
#include <ResourceManager.h>
#include <Renderable3D.h>

namespace easy_engine {
	namespace resource_manager {
		class ResourceManager3D : public ResourceManager {
			public:
				renderable::Renderable3D* LoadObj(std::string file_path);
		};
	}
}

#endif RESOURCE_MANAGER_3D_H