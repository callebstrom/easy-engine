#include <EasyEngine/eepch.h>

#include <filesystem>

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/resource/Texture.h>
#include <EasyEngine/Logger.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include <stb/stb_image_resize.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace easy_engine {
  namespace resource_manager {
    std::string ResourceManager::LoadFileAsString(std::string path) {
      std::string result;
      std::ifstream in(path, std::ios::in | std::ios::binary);
      if (in) {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
        ;
      }
      else {
        EE_CORE_ERROR("Could not open file '{0}'", path);
      }

      return result;
    }

    resource::Texture* ResourceManager::LoadTextureFromFile(std::string path) {
      auto texture = new resource::Texture();

      int width, height, bpp;

      unsigned char* decompressed_pixel_data = stbi_load(path.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

      auto failure = stbi_failure_reason();

      texture->file_path = path;
      texture->width = width;
      texture->height = height;
      texture->bpp = STBI_rgb_alpha;
      texture->raw = decompressed_pixel_data;

      return texture;
    }


    resource::Texture* ResourceManager::LoadTextureFromBuffer(void* data, size_t size) {
      auto texture = new resource::Texture();

      int width, height, bpp;
      unsigned char* decompressed_pixel_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(data), size, &width, &height, &bpp, 4);
      EE_CORE_TRACE("Loaded texture from memory, bpp: {}, width: {}px, height: {}px", bpp, width, height);

      texture->width = width;
      texture->height = height;
      texture->bpp = 4;
      texture->raw = decompressed_pixel_data;

      return texture;
    }
  }
}