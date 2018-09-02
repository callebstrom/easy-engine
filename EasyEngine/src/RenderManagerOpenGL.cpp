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
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glfwTerminate();
		}

		void RenderManagerOpenGL::Render() {

			// Set background to dark grey
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Consume the render queue and create VAO:s for each renderable in queue
			this->ConsumeRenderQueue();

			while (!glfwWindowShouldClose(this->window_)) {
				this->UpdateFpsCounter();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
				// Draw to the entire window
				glViewport(
					0, 
					0, 
					atoi(this->render_config_->Get(c_params_::RESOLUTION_X).c_str()),
					atoi(this->render_config_->Get(c_params_::RESOLUTION_Y).c_str())
				);

				glfwPollEvents();

				if (glfwGetKey(this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(this->window_, GL_TRUE);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				for (int i = 0; i < sizeof(this->vao_); i++) {
					// Activate the triangle vertex array object
					glBindVertexArray(this->vao_[i]);

					// Draw triangles
					glDrawArrays(GL_TRIANGLES, 0, sizeof(this->vao_[i]));
				}

				glfwSwapBuffers(this->window_);
			}

			// Clean-up
			glDeleteProgram(this->shader_program_);
			glDeleteShader(this->fragment_shader_);
			glDeleteShader(this->vertex_shader_);
			glDeleteBuffers(1, &this->vbo_[0]);
		}

		// Convert render queue to VBO:s 
		void RenderManagerOpenGL::ConsumeRenderQueue() {	
			log->debug("Consuming render queue");
			log->debug("Number of renderables in queue: " + std::to_string(this->render_queue.size()));

			GLsizei vao_size = this->render_queue.size();
			this->vao_ = (GLuint*)malloc(vao_size);
			glGenVertexArrays(vao_size, this->vao_);
			log->debug("Generated " + std::to_string(vao_size) + " vertex array object(s)");
			
			GLsizei vbo_size = this->render_queue.size() * 2;
			this->vbo_ = (GLuint*)malloc(vbo_size);
			glGenBuffers(vbo_size, this->vbo_);
			log->debug("Generated " + std::to_string(vbo_size) + " vertex buffer object(s)");

			int i = 0;
			for (auto &element : this->render_queue) {
				renderable::Renderable3D* renderable = static_cast<renderable::Renderable3D*>(element);

				// Set active VAO
				glBindVertexArray(this->vao_[i]);

				// Set active VBO to position VBO
				glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[i]);
				GLfloat* vertex_array = renderable->GetVertexArray();
				uint32_t no_of_coordinates = renderable->vertex_count * 3; // Each vertex has 3 coordinates of type float
				// Upload position data to a VBO
				glBufferData(
					GL_ARRAY_BUFFER, 
					no_of_coordinates * sizeof(float), // Bytes to copy
					vertex_array, 
					GL_STATIC_DRAW
				);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

				// Randomize colors for each vertex
				std::vector<float> color_array = {};

				for (uint32_t v = 0; v < renderable->vertex_count * 3; v++) {
					color_array.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				}

				// Set active VBO to color VBO
				glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[i+1]);
				log->debug("Triangle color VBO id: " + std::to_string(this->vbo_[i+1]));

				// Handle normals
				float* normals_array = renderable->GetVertexNormalArray(&RenderManagerOpenGL::ComputeNormals);

				// Upload color data to a VBO
				glBufferData(
					GL_ARRAY_BUFFER,
					no_of_coordinates * sizeof(float), // Each vertex is colored
					&color_array[0], // Use the vertex array for colors
					GL_STATIC_DRAW
				);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

				i += 2;
			}
		}

		void RenderManagerOpenGL::ComputeNormals(renderable::Renderable3D* renderable) {
			std::vector<glm::vec3> normals;
			normals.resize(renderable->vertex_count, glm::vec3(0.0, 0.0, 0.0));

			std::vector<ushort_t>& faces = renderable->faces_;
			std::vector<glm::vec4>vertices;
			
			ToGLMVertices(renderable->vertices_, vertices);

			for (int i = 0; i < faces.size(); i += 3) {
				GLushort ia = faces[i];
				GLushort ib = faces[i + 1];
				GLushort ic = faces[i + 2];
				glm::vec3 normal = glm::normalize(glm::cross(
					glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
					glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
				normals[ia] = normals[ib] = normals[ic] = normal;
			}

			// TODO convert normals to Eigen::MatrixX3f and add to renderable->vertex_normals_
		}

		void RenderManagerOpenGL::ToGLMVertices(Eigen::MatrixX3f& from_vertices, std::vector<glm::vec4>& to_vertices) {
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