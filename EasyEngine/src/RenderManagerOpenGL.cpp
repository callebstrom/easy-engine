#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

namespace easy_engine {
	namespace render_manager {

		typedef configuration::RenderConfigurationParams c_params_;

		logger::Logger* RenderManagerOpenGL::log = new logger::Logger("RenderManagerOpenGL");
		
		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration_t* rc) {
			this->render_config_ = rc;
			
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			int resX = atoi(this->render_config_->Get(c_params_::RESOLUTION_X).c_str());
			int resY = atoi(this->render_config_->Get(c_params_::RESOLUTION_Y).c_str());

			// this->window_ = glfwCreateWindow(resX, resY, "Easy	Engine", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
			this->window_ = glfwCreateWindow(resX, resY, "EasyEngine", nullptr, nullptr); // Windowed
							
			glfwMakeContextCurrent(this->window_);

			glewExperimental = GL_TRUE;
			glewInit();
			
			log->debug("Renderer: " + std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER)))));
			log->debug("OpenGL version supported: " + std::string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))));

			// tell GL to only draw onto a pixel if the shape is closer to the viewer
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

			// CAMERA
			glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)720 / (float)1280, 0.1f, 100.0f);
			glm::mat4 View = glm::lookAt(
				glm::vec3(2, 2, 2), // Camera is at (4,3,3), in World Space
				glm::vec3(0, 0, 0), // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
			glm::mat4 Model = glm::mat4(1.0f);
			glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
			GLuint matrix_id = glGetUniformLocation(this->vertex_shader_, "MVP");
			glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
			// CAMERA_END
		};

		void RenderManagerOpenGL::AddRenderable(renderable::Renderable* renderable) {
			RenderManager::AddRenderable(renderable);
			this->GenerateObjectIndex(renderable);
		}

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glDeleteProgram(this->shader_program_);
			glDeleteShader(this->fragment_shader_);
			glDeleteShader(this->vertex_shader_);
			glfwTerminate();
		}

		void RenderManagerOpenGL::Render() {

			if (glfwWindowShouldClose(this->window_)) {
				log->warning("Window should close");
				return;
			}
			
			this->UpdateFpsCounter();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwPollEvents();

			if (glfwGetKey(this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(this->window_, GL_TRUE);

			for (auto &object_index : this->object_indices_) {
				// Activate the triangle vertex array object
				glBindVertexArray(object_index.vao);

				// Draw vertices based on faces
				glDrawElements(GL_TRIANGLES, object_index.ebo_size, GL_UNSIGNED_SHORT, NULL);
			}

			glfwSwapBuffers(this->window_);
		}

		void RenderManagerOpenGL::GenerateObjectIndex(renderable::Renderable* renderable_) {

			renderable::Renderable3D* renderable = static_cast<renderable::Renderable3D*>(renderable_);
			ObjectIndexOpenGL object_index;

			glGenVertexArrays(1, &object_index.vao);
			log->debug("Generated vertex array object for " + renderable->name);

			// Set active VAO
			glBindVertexArray(object_index.vao);

			GLuint vbo, ebo;

			glGenBuffers(1, &vbo);
			log->debug("Generated vertex buffer object for " + renderable->name);

			glGenBuffers(1, &ebo);
			log->debug("Generated element array for " + renderable->name);

			// Set active VBO to position VBO
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glEnableVertexAttribArray(0);

			// Upload position data to a VBO
			glBufferData(
				GL_ARRAY_BUFFER,
				renderable->vertices_.size() * sizeof(GLfloat), // Bytes to copy
				renderable->vertices_.data(),
				GL_STATIC_DRAW
			);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0); // Tell OpenGL about our data format
						
			// Create an element array
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); 
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				renderable->vertex_indices_.size() * sizeof(GLushort),
				&renderable->vertex_indices_[0],
				GL_STATIC_DRAW
			);

			// Unbind VAO
			glBindVertexArray(0);

			// VBO and EBO can be deleted as VAO hold a reference to these
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);

			object_index.ebo_size = renderable->vertex_indices_.size();

			this->object_indices_.push_back(object_index);
		}

		void RenderManagerOpenGL::DrawGrid(float groundLevel) {
			GLfloat extent = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
			GLfloat stepSize = 20.0f;  // The size of the separation between points

			glColor3ub(255, 255, 255);

			// Draw our ground grid
			glBegin(GL_LINES);
			for (GLint loop = -extent; loop < extent; loop += stepSize)
			{
				// Draw lines along Z-Axis
				glVertex3f(loop, groundLevel, extent);
				glVertex3f(loop, groundLevel, -extent);

				// Draw lines across X-Axis
				glVertex3f(-extent, groundLevel, loop);
				glVertex3f(extent, groundLevel, loop);
			}
			glEnd();
		}

		std::vector<glm::vec3> RenderManagerOpenGL::ComputeNormals(renderable::Renderable3D* renderable) {
			std::vector<glm::vec3> normals;
			normals.resize(renderable->vertex_count, glm::vec3(0.0, 0.0, 0.0));

			std::vector<ushort_t> faces = renderable->faces_;
			std::vector<glm::vec4>vertices;
			
			RenderManagerOpenGL::ToGLMVertices(renderable->vertices_, vertices);

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
			int rows = from_vertices.rows();
			int cols = from_vertices.cols();

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

		void RenderManagerOpenGL::UpdateFpsCounter() {
			static double previous_seconds = glfwGetTime();
			static int frame_count;
			double current_seconds = glfwGetTime();
			double elapsed_seconds = current_seconds - previous_seconds;
			if (elapsed_seconds > 1) {
				previous_seconds = current_seconds;
				double fps = (double)frame_count / elapsed_seconds;

				char tmp[128];
				sprintf_s(tmp, 128, "FPS: %f", fps);

				glfwSetWindowTitle(this->window_, tmp);
				frame_count = 0;
			}
			frame_count++;
			
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

			if (vertex_status != GL_TRUE) {
				const std::string message = "Could not compile vertex shader";
				log->fatal(message);
			} else if (fragment_status != GL_TRUE) {
				const std::string message = "Could not compile fragment shader";
				log->fatal(message);
			}

			this->shader_program_ = glCreateProgram();
			glAttachShader(this->shader_program_, this->vertex_shader_);
			glAttachShader(this->shader_program_, this->fragment_shader_);

			glBindFragDataLocation(this->shader_program_, 0, "outColor");

			glLinkProgram(this->shader_program_);
			glUseProgram(this->shader_program_);

			char shader_log_buffer[512];
			glGetShaderInfoLog(this->vertex_shader_, 512, NULL, shader_log_buffer);

			if(shader_log_buffer[0] != NULL)
				log->debug("Shader compilation log: " + std::string(shader_log_buffer));
		}

	}
}