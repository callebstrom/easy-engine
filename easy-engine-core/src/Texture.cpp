#include <EasyEngine/eepch.h>
#include <EasyEngine/renderable/Texture.h>

namespace easy_engine {
	namespace renderable {
		Texture::Texture(const std::string & file_path)
			: file_path(file_path), raw(nullptr), width(0), height(0) {

		}
	}
}