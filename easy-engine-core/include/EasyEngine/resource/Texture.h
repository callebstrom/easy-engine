#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

namespace easy_engine {
	namespace resource {
		class EASY_ENGINE_API Texture {

		public:
			uint32_t renderer_id;
			std::string file_path;
			byte* raw;
			int width, height, bpp;

			Texture();
		};
	}
}
#endif // !TEXTURE_H