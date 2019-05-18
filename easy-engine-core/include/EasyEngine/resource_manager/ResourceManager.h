#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

#include <EasyEngine/renderable/Texture.h>

namespace easy_engine {
	namespace resource_manager {

		using renderable::Texture;

		class EASY_ENGINE_API ResourceManager {
		public:
			std::string GetEngineDirectory();
			std::shared_ptr<Texture> LoadTexture(std::string file_path);
		protected:
			byte* resourceCache;
			byte* LoadResourceByName(std::string pathRelativeToBase);
		};
	}
}
#endif // !RESOURCE_MANAGER_H
