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
#include <EasyEngine/Common.h>
#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/renderable/Renderable3D.h>

namespace easy_engine {
	namespace resource_manager {
		class EASY_ENGINE_API ResourceManager3D : public ResourceManager {
			public:
				renderable::Renderable3D* LoadObj(std::string file_path);
				
		};
	}
}

#endif RESOURCE_MANAGER_3D_H