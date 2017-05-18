#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <iostream>
#include <fstream>
#include <thread>

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

			glGenVertexArrays(1, &this->vao_);
			glBindVertexArray(this->vao_);

			glGenBuffers(1, &this->vbo_);
			std::cout << "[DEBUG] VBO identifier is " << this->vbo_ << std::endl;

			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);

			this->LoadShaders();
			
			std::cout << "[DEBUG] Shader program identifier: " << this->shader_program_ << std::endl;
			
			// Get and enable shader pos attrib
			glBindAttribLocation(this->shader_program_, this->pos_attrib_, "position");
			glEnableVertexAttribArray(this->pos_attrib_);
			glVertexAttribPointer(
				this->pos_attrib_, 
				2, 
				GL_FLOAT, 
				GL_FALSE,
				5 * sizeof(float), 
				0
			);
			std::cout << "[DEBUG] Shader position attrib location: " << this->pos_attrib_ << std::endl;

			// Get and enable shader color attrib
			glBindAttribLocation(this->shader_program_, this->col_attrib_, "color");
			glEnableVertexAttribArray(this->col_attrib_);
			glVertexAttribPointer(
				this->col_attrib_, 
				3, // 3 verticies in total
				GL_FLOAT, 
				GL_FALSE,
				5 * sizeof(float), // Size of each vertex (pos vec2 + color vec3)
				(void*)(2 * sizeof(float)) // Offset for color vec3
			);
			std::cout << "[DEBUG] Shader color attrib location: " << this->col_attrib_ << std::endl;
		
			// Get shader uniform attrib
			glBindAttribLocation(this->shader_program_, this->uniform_attrib_, "triangleColor");
			std::cout << "[DEBUG] Shader uniform attrib location: " << this->uniform_attrib_ << std::endl;

		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glfwTerminate();
		}

		void RenderManagerOpenGL::Render() {

			// TEST
			float vertices[] = {
				0.0f, 0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
				0.5f,-0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
				-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			while (!glfwWindowShouldClose(this->window_)) {

				glfwSwapBuffers(this->window_);
				glfwPollEvents();

				if (glfwGetKey(this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(this->window_, GL_TRUE);
				
				// Clear the screen to black
				glClearColor(0.5f, 0.0f, 0.0f, 0.5f);
				glClear(GL_COLOR_BUFFER_BIT);
				
				// Draw a triangle from the 3 vertices
				glDrawArrays(GL_TRIANGLES, 0, 3);

			}

			// Cleaup
			glDeleteProgram(this->shader_program_);
			glDeleteShader(this->fragment_shader_);
			glDeleteShader(this->vertex_shader_);
			glDeleteBuffers(1, &this->vbo_);
		}

		// Convert render queue to vertex_buffer_data_ 
		void RenderManagerOpenGL::ConsumeRenderQueue()
		{
			this->vertex_buffer_data_.clear();
			for (auto &element : this->render_queue) {
				GLfloat* vertex_array = static_cast<renderable::Renderable3D*>(element)->GetVertexArray();
				for (int i = 0; i < sizeof(vertex_array); i++)
					this->vertex_buffer_data_.push_back(vertex_array[i]);
			}
		}

		void RenderManagerOpenGL::LoadShaders() {
			std::ifstream vertex_in(this->render_config_->Get("vertex_shader.source_location"));
			std::string vertex_contents((std::istreambuf_iterator<char>(vertex_in)),
				std::istreambuf_iterator<char>());

			std::ifstream fragment_in(this->render_config_->Get("fragment_shader.source_location"));
			std::string shader_contents((std::istreambuf_iterator<char>(fragment_in)),
				std::istreambuf_iterator<char>());

			const char* vertex_source = vertex_contents.c_str();
			const char* fragment_source = shader_contents.c_str();

			if (vertex_source == "")
				throw std::runtime_error("Empty vertex shader source");
			else if (fragment_source == "")
				throw std::runtime_error("Empty vertex shader source");
			
			this->vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->vertex_shader_, 1, &vertex_source, NULL);
			glCompileShader(this->vertex_shader_);

			this->fragment_shader_ = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->fragment_shader_, 1, &fragment_source, NULL);
			glCompileShader(this->fragment_shader_);

			GLint vertex_status, fragment_status;
			glGetShaderiv(this->vertex_shader_, GL_COMPILE_STATUS, &vertex_status);
			glGetShaderiv(this->vertex_shader_, GL_COMPILE_STATUS, &fragment_status);

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