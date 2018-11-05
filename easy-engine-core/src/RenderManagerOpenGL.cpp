﻿#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/configuration/RenderConfiguration.h>

using easy_engine::logger::Logger;

void GLAPIENTRY Debug(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam) {
	// log->debug(message​);
	// log->debug("hello");
	std::cout << "hello";
};

namespace easy_engine {
	namespace render_manager {
		typedef configuration::RenderConfigurationParams c_params_;

		Logger* RenderManagerOpenGL::log = new Logger("RenderManagerOpenGL");
		
		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration_t* rc) {
			this->render_config_ = rc;

			glewExperimental = GL_TRUE;
			GLenum glew_error = glewInit();

			if (glew_error != GLEW_OK) {
				log->fatal("Failed to init GLEW: " + boost::lexical_cast<std::string>(glewGetErrorString(glew_error)));
			}

			glEnable(GL_DEPTH_TEST); // enable depth-testing
			glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

			this->LoadShaders();

			// Set background to dark grey
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Draw to the entire window
			glViewport(
				0,
				0,
				atoi(this->render_config_->Get(c_params_::RESOLUTION_X).c_str()),
				atoi(this->render_config_->Get(c_params_::RESOLUTION_Y).c_str())
			);
			
			// Don't render triangles with normal facing away from camera
			glEnable(GL_CULL_FACE);
			// glDebugMessageCallback(&Debug, nullptr);
		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glDeleteProgram(this->shader_program_);
			glDeleteShader(this->fragment_shader_);
			glDeleteShader(this->vertex_shader_);
		}

		void RenderManagerOpenGL::Render(renderable::Renderable* renderable_) {

			renderable::Renderable3D* renderable = static_cast<renderable::Renderable3D*>(renderable_);

			// Should the object index be built lazily?
			if (this->object_indices_.find(renderable->name) == this->object_indices_.end()) {
				this->GenerateObjectIndex(renderable);
			}

			ObjectIndex object_index = this->object_indices_.at(renderable->name);

			/*if (glfwWindowShouldClose(this->window_)) {
				glfwTerminate();
				return;
			}*/

			// this->UpdateFpsCounter();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/*if (glfwGetKey(this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(this->window_, GL_TRUE);*/

			// TODO this should probably happen at the same time as the ObjectIndex is built..
			renderable::Texture* texture = renderable->GetTexture().get();

			if (texture != nullptr) {
				glBindTexture(GL_TEXTURE_2D, texture->GetRendererId());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetRaw());
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			glBindVertexArray(object_index.vao);

			GLint uniMvp = glGetUniformLocation(this->shader_program_, "mvp");
			glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(this->mvp));

			glDrawElements(GL_TRIANGLES, object_index.ebo_size, GL_UNSIGNED_SHORT, NULL);
		}

		void RenderManagerOpenGL::GetRenderInfo() {
			log->debug("Renderer: " + std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER)))));
			log->debug("OpenGL version supported: " + std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))));
		}

		// TODO this should be handled by WindowManager using glfwSetWindowUserPointer
		void RenderManagerOpenGL::UpdateCameraAngle(double x, double y) {

			static double lastTime = glfwGetTime();
			double currentTime = glfwGetTime();
			float deltaTime = float(currentTime - lastTime);

			// position
			glm::vec3 position = glm::vec3(0, 0, 10);

			// horizontal angle : toward -Z
			float horizontalAngle = 3.14f;

			// vertical angle : 0, look at the horizon
			float verticalAngle = 0.0f;
			
			static const float mouseSpeed = 0.1f;

			horizontalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_X)) / 2 - x);
			verticalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_Y)) / 2 - y);

			glm::vec3 direction = glm::vec3(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
			);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - 3.14f / 2.0f),
				0,
				cos(horizontalAngle - 3.14f / 2.0f)
			);
			
			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			float FoV = 45.0f;

			static glm::mat4 projection_matrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);

			glm::mat4 view_matrix;

			// Camera matrix
			view_matrix = glm::lookAt(
				position,				// Camera is here
				position + direction,	// and looks here : at the same position, plus "direction"
				up						// Head is up (set to 0,-1,0 to look upside-down)
			);

			glm::mat4 model_matrix = glm::mat4(1.0);
			this->mvp = projection_matrix * view_matrix * glm::scale(model_matrix, glm::vec3(2, 2, 2));
			lastTime = lastTime + deltaTime;
		}

		void RenderManagerOpenGL::GenerateObjectIndex(renderable::Renderable* renderable_) {

			renderable::Renderable3D* renderable = static_cast<renderable::Renderable3D*>(renderable_);
			ObjectIndex object_index;

			glGenVertexArrays(1, &object_index.vao);
			log->debug("Generated vertex array object for " + renderable->name);

			// Set active VAO
			glBindVertexArray(object_index.vao);

			GLuint vbo, ebo, color_buffer;

			glGenBuffers(1, &vbo);
			log->debug("Generated vertex buffer object for " + renderable->name);

			glGenBuffers(1, &ebo);
			log->debug("Generated element array for " + renderable->name);

			glGenBuffers(1, &color_buffer);

			// Set active VBO to position VBO
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glEnableVertexAttribArray(0);

			// Upload position data to a VBO
			glBufferData(
				GL_ARRAY_BUFFER,
				renderable->GetVertices().size() * sizeof(GLfloat), // Bytes to copy
				renderable->GetVertices().data(),
				GL_STATIC_DRAW
			);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0); // Tell OpenGL about our data format

			// RANDOM_COLOR_PER_VERTEX
			std::vector<GLfloat> color_buffer_data;
			for (int c = 0; c < renderable->GetVertices().size() / 3; c++) {
				color_buffer_data.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
			}

			glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
			glBufferData(
				GL_ARRAY_BUFFER, 
				color_buffer_data.size() * sizeof(GLfloat),
				&color_buffer_data[0],
				GL_STATIC_DRAW
			);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Tell OpenGL about our data
			// !RANDOM_COLOR_PER_VERTEX

			// Create an element array
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); 
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				renderable->GetVertices().size() * sizeof(GLushort),
				&renderable->GetVertexIndices()[0],
				GL_STATIC_DRAW
			);

			// Unbind VAO
			glBindVertexArray(0);

			// VBO and EBO can be deleted as VAO hold a reference to these
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
			glDeleteBuffers(1, &color_buffer);

			object_index.ebo_size = renderable->GetVertices().size();
			
			this->object_indices_.insert(std::pair<std::string, ObjectIndex>(renderable->name, object_index));

			if (renderable->GetTexture().get() != nullptr) {
				GLuint renderer_id;
				glGenTextures(1, &renderer_id);
				renderable->GetTexture()->SetRendererId(renderer_id);
			}

		}

		std::vector<glm::vec3> RenderManagerOpenGL::ComputeNormals(renderable::Renderable3D* renderable) {
			std::vector<glm::vec3> normals;
			normals.resize(renderable->GetVertexCount(), glm::vec3(0.0, 0.0, 0.0));

			std::vector<ushort_t> faces = renderable->GetFaces();
			std::vector<glm::vec4>vertices;
			
			RenderManagerOpenGL::ToGLMVertices(renderable->GetVertices(), vertices);

			log->info("faces.size(): " + faces.size());
			log->debug("vertices.size(): " + vertices.size());

			for (int i = 0; i < faces.size(); i += 3) {
				ushort_t ia = faces[i];
				ushort_t ib = faces[i + 1];
				ushort_t ic = faces[i + 2];

				glm::vec3 ib_ia_diff = glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]);
				glm::vec3 ic_ia_diff = glm::vec3(vertices[ic]) - glm::vec3(vertices[ia]);

				glm::vec3 normal = glm::normalize(glm::cross(
					ib_ia_diff,
					ic_ia_diff));
				normals[ia] = normals[ib] = normals[ic] = normal;
			}

			return normals;
		}

		void RenderManagerOpenGL::ToGLMVertices(Eigen::Matrix<float, -1, 3, Eigen::RowMajor>& from_vertices, std::vector<glm::vec4>& to_vertices) {
			int64_t rows = from_vertices.rows();
			int64_t cols = from_vertices.cols();

			for (int i = 0; i < rows; i++) {
				for (int x = 0; x < cols; x++) {

					glm::vec4 vec = glm::vec4();
					vec.x = from_vertices(i, 0);
					vec.y = from_vertices(i, 0);
					vec.z = from_vertices(i, 0);
					vec.w = 1.0f;

					to_vertices.push_back(vec);
				}
			}
		}

		void RenderManagerOpenGL::LoadShaders() {
			std::ifstream vertex_in(this->render_config_->Get(c_params_::VERTEX_SHADER_SOURCE_LOCATION));
			std::string vertex_contents((std::istreambuf_iterator<char>(vertex_in)),
				std::istreambuf_iterator<char>());

			std::ifstream fragment_in(this->render_config_->Get(c_params_::FRAGMENT_SHADER_SOURCE_LOCATION));
			std::string fragment_contents((std::istreambuf_iterator<char>(fragment_in)),
				std::istreambuf_iterator<char>());

			const char* vertex_source = vertex_contents.c_str();
			const char* fragment_source = fragment_contents.c_str();

			if (vertex_source == "")
				throw std::runtime_error("Empty vertex shader source");
			else if (fragment_source == "")
				throw std::runtime_error("Empty fragment shader source");
			
			this->vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->vertex_shader_, 1, &vertex_source, NULL);
			glCompileShader(this->vertex_shader_);

			this->fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(this->fragment_shader_, 1, &fragment_source, NULL);
			glCompileShader(this->fragment_shader_);

			GLint vertex_status, fragment_status;
			glGetShaderiv(this->vertex_shader_, GL_COMPILE_STATUS, &vertex_status);
			glGetShaderiv(this->fragment_shader_, GL_COMPILE_STATUS, &fragment_status);

			char shader_log_buffer[512];

			if (vertex_status != GL_TRUE) {
				const std::string message = "Could not compile vertex shader: ";
				glGetShaderInfoLog(this->vertex_shader_, 256, NULL, shader_log_buffer);
				log->fatal(message + shader_log_buffer);
			} else if (fragment_status != GL_TRUE) {
				const std::string message = "Could not compile fragment shader: ";
				glGetShaderInfoLog(this->fragment_shader_, 256, NULL, shader_log_buffer);
				log->fatal(message + shader_log_buffer);
			}

			this->shader_program_ = glCreateProgram();
			glAttachShader(this->shader_program_, this->vertex_shader_);
			glAttachShader(this->shader_program_, this->fragment_shader_);

			glBindFragDataLocation(this->shader_program_, 1, "outColor");

			glLinkProgram(this->shader_program_);
			glUseProgram(this->shader_program_);
		}

	}
}