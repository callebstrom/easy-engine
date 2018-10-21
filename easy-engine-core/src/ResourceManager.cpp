#define STB_IMAGE_IMPLEMENTATION

#include <ResourceManager.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Texture.h>
#include <stb/std_image.h>

namespace easy_engine {
	namespace resource_manager {
		byte* ResourceManager::LoadResourceByName(std::string path_relative_to_base) {
			return nullptr;
		}

		std::shared_ptr<Texture> ResourceManager::LoadTexture(std::string file_path) {
			Texture* texture = new Texture(file_path);
			stbi_set_flip_vertically_on_load(1);

			int width, height, bpp;
			stbi_load(file_path.c_str(), &width, &height, &bpp, 4);

			texture->SetWidth(width);
			texture->SetHeight(height);
			texture->SetBitsPerPixel(bpp);

			return std::shared_ptr<Texture>(texture);
		}
	}
}