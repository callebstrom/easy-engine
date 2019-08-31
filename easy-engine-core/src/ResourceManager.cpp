#include <EasyEngine/eepch.h>

#include <experimental/filesystem>

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/resource/Texture.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include <stb/stb_image_resize.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace easy_engine {
	namespace resource_manager {
		byte* ResourceManager::LoadResourceByName(std::string path_relative_to_base) {
			return nullptr;
		}

		resource::Texture* ResourceManager::LoadTextureFromFile(std::string path) {
			auto texture = new resource::Texture();

			int width, height, bpp;

			unsigned char* decompressed_pixel_data = stbi_load(path.c_str(), &width, &height, &bpp, 0);

			auto failure = stbi_failure_reason();

			texture->file_path = path;
			texture->width = width;
			texture->height = height;
			texture->bpp = bpp;
			texture->raw = decompressed_pixel_data;

			return texture;
		}


		resource::Texture* ResourceManager::LoadTextureFromBuffer(void* data, size_t size) {
			auto texture = new resource::Texture();

			int width, height, bpp;
			unsigned char* decompressed_pixel_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(data), size, &width, &height, &bpp, 4);
			delete[] data;

			texture->width = width;
			texture->height = height;
			texture->bpp = bpp;
			texture->raw = decompressed_pixel_data;

			return texture;
		}
	}
}