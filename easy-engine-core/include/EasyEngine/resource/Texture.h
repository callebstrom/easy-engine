#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

namespace easy_engine {
	namespace resource {

		enum TextureType {
			NONE = 0x0,
			DIFFUSE = 0x1,
			SPECULAR = 0x2,
			AMBIENT = 0x3,
			EMISSIVE = 0x4,
			HEIGHT = 0x5,
			NORMALS = 0x6,
			SHININESS = 0x7,
			OPACITY = 0x8,
			DISPLACEMENT = 0x9,
			LIGHTMAP = 0xA,
			REFLECTION = 0xB
		};

		class EASY_ENGINE_API Texture {

		public:
			uint32_t renderer_id;
			std::string file_path;
			byte* raw;
			int width, height, bpp;

			TextureType type = TextureType::NONE;

			Texture();
		};
	}
}
#endif // !TEXTURE_H