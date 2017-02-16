#pragma once
#include <RenderManager.h>

#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>
#include <vector>

namespace easy_engine {
	namespace render_manager {
		class RenderManagerOpenGL : public RenderManager {
			public:
				RenderManagerOpenGL(configuration::RenderConfiguration* rc);
				void Render();

				std::vector<GLfloat> vertex_buffer_data_;
				GLuint vertex_buffer_;
		};

	}
}