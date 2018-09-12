#pragma once

#include <GL/glew.h>

namespace easy_engine {
	namespace render_manager {
		struct ObjectIndexOpenGL {
			GLuint vao;
			GLuint ebo_size;
		};
	}
}