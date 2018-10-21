#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

#include <Common.h>
#include <Texture.h>

namespace easy_engine {
	namespace resource_manager {

		using renderable::Texture;

		class DLLEXPORT ResourceManager {
			protected:
				byte* resourceCache;
				byte* LoadResourceByName(std::string pathRelativeToBase);
				std::shared_ptr<Texture> LoadTexture(std::string file_path);
		};
	}
}
#endif // !RESOURCE_MANAGER_H
