#ifndef RENDER_MANAGER_OPEN_GL_H
#define RENDER_MANAGER_OPEN_GL_H
#pragma once

#include <EasyEngine/Common.h>

#include <GL/glew.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glfw3.h>

#include <boost/lexical_cast.hpp>

#include <EasyEngine/Logger.h>
#include <EasyEngine/render_manager/RenderManager.h>
#include <EasyEngine/renderable/Renderable3D.h>
#include <EasyEngine/render_manager/ObjectIndex.h>

namespace easy_engine {

	namespace render_manager {

		class EASY_ENGINE_API RenderManagerOpenGL : public RenderManager {
		public:
			RenderManagerOpenGL(configuration::RenderConfiguration_t* rc);
			RenderManagerOpenGL::~RenderManagerOpenGL();

			static std::vector<glm::vec3> ComputeNormals(renderable::Renderable3D* renderable);

			void Render(renderable::Renderable* renderable) override;
			void UpdateCameraAngle(double x, double y) override;

		private:
			std::vector<GLfloat> vertex_buffer_data_;

			void GetRenderInfo();
			void LoadShaders();
			void GenerateObjectIndex(renderable::Renderable* renderable);
			static void ToGLMVertices(Eigen::Matrix<float, -1, 3, Eigen::RowMajor>& from_vertices, std::vector<glm::vec4>& to_vertices);

			glm::mat4 mvp = glm::mat4(1.0);
			std::map<std::string, ObjectIndex> object_indices_;
			float last_time_;
			GLuint vertex_shader_;
			GLuint fragment_shader_;
			GLuint shader_program_;
			GLint pos_attrib_;
			GLint uniform_attrib_;
			GLint col_attrib_;
		};
	}
}
#endif // !RENDER_MANAGER_OPEN_GL_H
