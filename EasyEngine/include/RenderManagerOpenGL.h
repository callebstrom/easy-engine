#pragma once

#include <GL\glew.h>
#include <GL\glfw3.h>
#include <iostream>
#include <vector>

#include <Logger.h>
#include <RenderManager.h>
#include <Renderable3D.h>

#ifndef RENDER_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace render_manager {
		class RenderManagerOpenGL : public RenderManager {
			public:
				RenderManagerOpenGL(RenderConfiguration* rc);
				RenderManagerOpenGL::~RenderManagerOpenGL();
				void Render();

				std::vector<GLfloat> vertex_buffer_data_;
				GLFWwindow* window_;

			private:
				static logger::Logger* log;

				void LoadShaders();
				void ConsumeRenderQueue();
				void UpdateFpsCounter();

				GLuint* vbo_;
				GLuint* vao_;
				GLuint vertex_shader_;
				GLuint fragment_shader_;
				GLuint shader_program_;
				GLint pos_attrib_;
				GLint uniform_attrib_;
				GLint col_attrib_;
		};

	}
}
#endif