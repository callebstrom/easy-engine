#pragma once

#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GL\glfw3.h>
#include <glm\glm.hpp>

#include <Logger.h>
#include <RenderManager.h>
#include <Renderable3D.h>

#ifndef RENDER_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace render_manager {

		class RenderManagerOpenGL : public RenderManager {
			public:
				RenderManagerOpenGL(configuration::RenderConfiguration_t* rc);
				RenderManagerOpenGL::~RenderManagerOpenGL();
				void Render();
				static void ComputeNormals(renderable::Renderable3D* renderable);

				std::vector<GLfloat> vertex_buffer_data_;
				GLFWwindow* window_;

			private:
				static logger::Logger* log;

				void LoadShaders();
				void ConsumeRenderQueue();
				void UpdateFpsCounter();
				static void ToGLMVertices(Eigen::MatrixX3f& from_vertices, std::vector<glm::vec4>& to_vertices);

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