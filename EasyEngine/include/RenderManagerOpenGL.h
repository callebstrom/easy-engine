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

				std::vector<GLfloat> vertex_buffer_data_;
				GLFWwindow* window_;

			private:
				void LoadShaders();
				void ConsumeRenderQueue();

				GLuint vbo_;
				GLuint vao_;
				GLuint vertex_shader_;
				GLuint fragment_shader_;
				GLuint shader_program_;
				GLint pos_attrib_;
				GLint uni_color_;
		};

	}
}
#endif