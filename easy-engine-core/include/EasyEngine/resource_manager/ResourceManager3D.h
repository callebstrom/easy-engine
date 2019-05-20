#ifndef RESOURCE_MANAGER_3D_H
#define RESOURCE_MANAGER_3D_H
#pragma once

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/resource/Mesh.h>

namespace easy_engine {
	namespace resource_manager {
		class EASY_ENGINE_API ResourceManager3D : public ResourceManager {
		public:
			resource::Mesh* LoadObj(std::string file_path);

		};
	}
}

#endif RESOURCE_MANAGER_3D_H