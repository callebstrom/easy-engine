#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

namespace easy_engine {
	namespace render_manager {
		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration* rc) {
			this->render_config_ = rc;

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			int resX = atoi(this->render_config_->Get("resolution.x").c_str());
			int resY = atoi(this->render_config_->Get("resolution.y").c_str());

			// this->window_ = glfwCreateWindow(resX, resY, "EasyEngine", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
			this->window_ = glfwCreateWindow(resX, resY, "EasyEngine", nullptr, nullptr); // Windowed
							
			glfwMakeContextCurrent(this->window_);


			glewExperimental = GL_TRUE;
			glewInit();

			const GLubyte* renderer = glGetString(GL_RENDERER);
			const GLubyte* version = glGetString(GL_VERSION);
			std::cout << "Renderer: " << renderer << std::endl;
			std::cout << "OpenGL version supported: " << version << std::endl;

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

			/* float test_triangle_[9] = {
				-0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f
			};

			float test_square_[12] = {
				1.0f, 1.0f, 0.0f,
				1.0f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				0.5f, 1.0f, 0.0f
			};

			float test_triangle_color[9] = {
				0.5f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f,
				0.0f, 0.0f, 0.5f,
			};

			float test_square_color[12] = {
				0.5f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f,
				0.0f, 0.0f, 0.5f,
				0.5f, 0.5f, 0.0f
			};

			glGenVertexArrays(2, this->vao_);
			glGenBuffers(4, this->vbo_);

			// Set active VAO
			glBindVertexArray(this->vao_[0]);

			// Set active VBO to position VBO
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[0]);

			std::cout << "Triangle position VBO id: " << this->vbo_[0] << std::endl;
			// Upload data to VBO
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), test_triangle_, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Set active VBO to color VBO
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[1]);
			std::cout << "Triangle color VBO id: " << this->vbo_[1] << std::endl;

			// Upload data to VBO
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), test_triangle_color, GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Set active VAO
			glBindVertexArray(this->vao_[1]);

			// Set active VBO to position VBO
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[2]);

			std::cout << "Square position VBO id: " << this->vbo_[2] << std::endl;
			// Upload data to VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(test_square_) * sizeof(float), test_square_, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Set active VBO to color VBO
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[3]);
			std::cout << "Square color VBO id: " << this->vbo_[3] << std::endl;

			// Upload data to VBO
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), test_square_color, GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);*/

			this->ConsumeRenderQueue();

			while (!glfwWindowShouldClose(this->window_)) {

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
		void RenderManagerOpenGL::ConsumeRenderQueue()
		{	
			std::cout << "[DEBUG] Consuming render queue" << std::endl;
			std::cout << "[DEBUG] Number of renderables in queue: " << this->render_queue.size() << std::endl;

			int vao_size = this->render_queue.size();
			this->vao_ = (GLuint*)malloc(vao_size);
			glGenVertexArrays(vao_size, this->vao_);
			std::cout << "[DEBUG] Generated " << vao_size << " vertex array object(s)" << std::endl;
			
			int vbo_size = this->render_queue.size() * 2;
			this->vbo_ = (GLuint*)malloc(vbo_size);
			glGenBuffers(vbo_size, this->vbo_);
			std::cout << "[DEBUG] Generated " << vbo_size << " vertex buffer object(s)" << std::endl;

			int i = 0;
			for (auto &element : this->render_queue) {
				// Set active VAO
				glBindVertexArray(this->vao_[i]);
				// Set active VBO to position VBO
				glBindBuffer(GL_ARRAY_BUFFER, this->vbo_[i]);

				renderable::Renderable3D* renderable = static_cast<renderable::Renderable3D*>(element);

				GLfloat* vertex_array = renderable->GetVertexArray();

				// Upload data to VBO
				glBufferData(
					GL_ARRAY_BUFFER, 
					renderable->vertex_count * 3 * sizeof(float), // Each vertex has 3 coordinates of type float
					vertex_array, 
					GL_STATIC_DRAW
				);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(
					0, 
					3, 
					GL_FLOAT, 
					GL_FALSE, 
					0, 
					0
				);

				i++;
			}
		}

		void RenderManagerOpenGL::LoadShaders() {
			std::ifstream vertex_in(this->render_config_->Get("vertex_shader.source_location"));
			std::string vertex_contents((std::istreambuf_iterator<char>(vertex_in)),
				std::istreambuf_iterator<char>());

			std::ifstream fragment_in(this->render_config_->Get("fragment_shader.source_location"));
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

			if (vertex_status != GL_TRUE)
				throw new std::runtime_error("Could not compile vertex shader");
			else if (fragment_status != GL_TRUE)
				throw new std::runtime_error("Could not compile fragment shader");

			this->shader_program_ = glCreateProgram();
			glAttachShader(this->shader_program_, this->vertex_shader_);
			glAttachShader(this->shader_program_, this->fragment_shader_);

			glBindFragDataLocation(this->shader_program_, 0, "outColor");

			glLinkProgram(this->shader_program_);
			glUseProgram(this->shader_program_);

			char shader_log_buffer[512];
			glGetShaderInfoLog(this->vertex_shader_, 512, NULL, shader_log_buffer);

			if(shader_log_buffer[0] != NULL)
				std::cout << "[DEBUG] Shader compilation log: " << std::endl << shader_log_buffer;
		}

	}
}