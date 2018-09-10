#pragma once

#include <GL/glew.h>

#ifndef OBJECT_INDEX_OPEN_GL_H

namespace easy_engine {
	namespace render_manager {
		struct ObjectIndexOpenGL {
			GLuint vao;
			GLuint ebo_size;
		};
	}
}
#endif // !OBJECT_INDEX_OPEN_GL_H