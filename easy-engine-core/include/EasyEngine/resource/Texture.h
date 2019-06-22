#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

namespace easy_engine {
	namespace resource {

		enum TextureType {
			kNone = 0x0,
			kDiffuse = 0x1,
			kSpecular = 0x2,
			kAmbient = 0x3,
			kEmissive = 0x4,
			kHeight = 0x5,
			kNormals = 0x6,
			kShininess = 0x7,
			kOpacity = 0x8,
			kDisplacement = 0x9,
			kLightmap = 0xA,
			kReflection = 0xB
		};

		class EASY_ENGINE_API Texture {

		public:
			uint32_t renderer_id;
			std::string file_path;
			byte* raw;
			int width, height, bpp;

			TextureType type = TextureType::kNone;

			Texture();
		};
	}
}
#endif // !TEXTURE_H