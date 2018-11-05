#pragma once

#include <GL/glew.h>

namespace easy_engine {
	namespace render_manager {
		struct ObjectIndex {
			GLuint vao;
			GLuint ebo_size;

			bool operator< (const ObjectIndex &right) const {
				return vao < right.vao;
			}
		};
	}
}