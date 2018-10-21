#include <Texture.h>

namespace easy_engine {
	namespace renderable {
		void Texture::SetRendererId(uint32_t renderer_id) {
			this->renderer_id_ = renderer_id;
		};
		Texture::Texture(const std::string & file_path)
			: file_path_(file_path), raw_(nullptr), width_(0), height_(0) {

		}
	}
}