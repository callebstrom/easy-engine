#include <EasyEngine/eepch.h>
#include <EasyEngine/resource/Texture.h>

#include <stb/stb_image.h>

namespace easy_engine {
	namespace resource {
		Texture::Texture()
			: file_path(""), raw(nullptr), width(0), height(0) {

		}
		void Texture::Free() {
			free(raw);
		}
	}
}