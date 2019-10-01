#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#pragma once

namespace easy_engine {

	namespace resource {
		class Texture;
	}

	namespace resource_manager {

		class EASY_ENGINE_API ResourceManager {
		public:
			static auto LoadFileAsString(std::string pathRelativeToBase) -> std::string;
			static auto LoadTextureFromFile(std::string path) -> resource::Texture*;
			static auto LoadTextureFromBuffer(void* data, size_t size) -> resource::Texture*;
		};
	}
}
#endif // !RESOURCE_MANAGER_H
