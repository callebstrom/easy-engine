#include <EasyEngine/eepch.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/std_image.h>
#include <experimental/filesystem>

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/resource/Texture.h>

namespace easy_engine {
	namespace resource_manager {
		byte* ResourceManager::LoadResourceByName(std::string path_relative_to_base) {
			return nullptr;
		}

		std::string ResourceManager::GetEngineDirectory() {
			return std::experimental::filesystem::current_path().remove_filename().u8string();
		}

		std::shared_ptr<Texture> ResourceManager::LoadTexture(std::string file_path) {
			Texture* texture = new Texture(file_path);
			stbi_set_flip_vertically_on_load(1);

			int width, height, bpp;
			stbi_load(file_path.c_str(), &width, &height, &bpp, 4);

			texture->width = width;
			texture->height = height;
			texture->bpp = bpp;

			return std::shared_ptr<Texture>(texture);
		}
	}
}