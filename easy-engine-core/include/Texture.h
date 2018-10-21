#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <Common.h>

namespace easy_engine {
	namespace renderable {
		class Texture {
			private:
				uint32_t renderer_id_;
				std::string file_path_;
				byte* raw_;
				int width_, height_, bitsPerPixel_;

			public:
				inline uint32_t GetRendererId() const { return this->renderer_id_; };
				inline int GetWidth() const { return this->width_; };
				inline int GetHeight() const { return this->height_; };
				inline byte* GetRaw() const { return this->raw_; };

				void SetRendererId(uint32_t renderer_id);
				void SetWidth(int width) { this->width_ = width; };
				void SetHeight(int height) { this->height_ = height; };
				void SetBitsPerPixel(int bpp) { this->bitsPerPixel_ = bpp; };

				Texture(const std::string& file_path);
				
		};
	}
}
#endif // !TEXTURE_H