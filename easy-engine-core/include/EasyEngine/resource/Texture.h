#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

namespace easy_engine {
	namespace resource {
		class Texture {

		public:
			uint32_t renderer_id;
			std::string file_path;
			byte* raw;
			int width, height, bpp;

			Texture(const std::string& file_path);
		};
	}
}
#endif // !TEXTURE_H