#include <EasyEngine/eepch.h>
#include <EasyEngine/resource/Texture.h>

namespace easy_engine {
	namespace resource {
		Texture::Texture(const std::string& file_path)
			: file_path(file_path), raw(nullptr), width(0), height(0) {

		}
	}
}