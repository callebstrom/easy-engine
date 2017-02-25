#pragma once

#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>
#include <vector>

#include <RenderManager3D.h>

#ifndef RENDER_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace render_manager {
		class RenderManagerOpenGL : public RenderManager3D {
			public:
				RenderManagerOpenGL(configuration::RenderConfiguration* rc);
				
				void Render();
				void ConsumeRenderQueue();

				std::vector<GLfloat> vertex_buffer_data_;
				GLuint vertex_buffer_;
		};

	}
}
#endif