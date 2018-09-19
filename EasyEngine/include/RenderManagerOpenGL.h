#pragma once

#include <Common.h>

#include <GL/glew.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/lexical_cast.hpp>

#include <Logger.h>
#include <RenderManager.h>
#include <Renderable3D.h>
#include <ObjectIndex.h>

namespace easy_engine {

	namespace render_manager {

		class RenderManagerOpenGL : public RenderManager {
			public:
				RenderManagerOpenGL(configuration::RenderConfiguration_t* rc);
				RenderManagerOpenGL::~RenderManagerOpenGL();

				static std::vector<glm::vec3> ComputeNormals(renderable::Renderable3D* renderable);

				void Render(renderable::Renderable* renderable);
				void UpdateCameraAngle(double x, double y);

			private:
				static logger::Logger* log;
				std::vector<GLfloat> vertex_buffer_data_;

				void GetRenderInfo();
				void LoadShaders();
				void GenerateObjectIndex(renderable::Renderable* renderable);
				static void ToGLMVertices(Eigen::Matrix<float, -1, 3, Eigen::RowMajor>& from_vertices, std::vector<glm::vec4>& to_vertices);

				std::map<std::string, ObjectIndex> object_indices_;
				GLuint vertex_shader_;
				GLuint fragment_shader_;
				GLuint shader_program_;
				GLint pos_attrib_;
				GLint uniform_attrib_;
				GLint col_attrib_;				
		};
	}
}