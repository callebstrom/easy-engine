#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

namespace easy_engine {

	namespace resource {
		class Texture;
	}

	namespace resource_manager {

		class EASY_ENGINE_API ResourceManager {
		protected:
			byte* resourceCache;
			byte* LoadResourceByName(std::string pathRelativeToBase);
			static resource::Texture* LoadTextureFromFile(std::string path);
			static resource::Texture* LoadTextureFromBuffer(void* data, size_t size);
		};
	}
}
#endif // !RESOURCE_MANAGER_H
