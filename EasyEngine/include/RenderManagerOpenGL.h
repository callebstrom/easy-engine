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
				RenderManagerOpenGL::~RenderManagerOpenGL();
				
				void Render();
				void ConsumeRenderQueue();

				std::vector<GLfloat> vertex_buffer_data_;
				GLuint vertex_buffer_;
				GLFWwindow* window_;

			private:
				GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
		};

	}
}
#endif