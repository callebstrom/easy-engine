#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/lexical_cast.hpp>

#include <Logger.h>
#include <RenderManager.h>
#include <Renderable3D.h>
#include <ObjectIndexOpenGL.h>

#ifndef RENDER_MANAGER_3D_OPEN_GL_H
namespace easy_engine {
	namespace render_manager {

		class RenderManagerOpenGL : public RenderManager {
			public:
				RenderManagerOpenGL(configuration::RenderConfiguration_t* rc);
				RenderManagerOpenGL::~RenderManagerOpenGL();

				static std::vector<glm::vec3> ComputeNormals(renderable::Renderable3D* renderable);

				void Render();
				void AddRenderable(renderable::Renderable* renderable);

				std::vector<GLfloat> vertex_buffer_data_;
				GLFWwindow* window_;

			private:
				static logger::Logger* log;

				void LoadShaders();
				void UpdateFpsCounter();
				void DrawGrid(float groundLevel);
				void GenerateObjectIndex(renderable::Renderable* renderable);
				static void ToGLMVertices(Eigen::Matrix<float, -1, 3, Eigen::RowMajor>& from_vertices, std::vector<glm::vec4>& to_vertices);

				std::vector<ObjectIndexOpenGL> object_indices_;
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