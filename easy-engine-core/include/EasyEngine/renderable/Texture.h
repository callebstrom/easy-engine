#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

namespace easy_engine {
	namespace renderable {
		class Texture {

			public:
				uint32_t renderer_id;
				std::string file_path;
				byte* raw;
				int width, height, bitsPerPixel;

				Texture(const std::string& file_path);
		};
	}
}
#endif // !TEXTURE_H