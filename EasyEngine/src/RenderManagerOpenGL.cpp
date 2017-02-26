#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <iostream>
#include <fstream>
#include <thread>

namespace easy_engine {
	namespace render_manager {
		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration* rc) {
			this->render_config_ = rc;
			this->vertex_buffer_data_ = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f,  1.0f, 0.0f,
			};
			
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
		};

		RenderManagerOpenGL::~RenderManagerOpenGL() {
			glfwTerminate();
		}

		void RenderManagerOpenGL::Render() {

			GLuint vertexBuffer;
			glGenBuffers(1, &vertexBuffer);

			printf("%u\n", vertexBuffer);
			while (!glfwWindowShouldClose(this->window_))
			{
				glfwSwapBuffers(this->window_);
				glfwPollEvents();

				if (glfwGetKey(this->window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(this->window_, GL_TRUE);
			}
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

		GLuint RenderManagerOpenGL::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
			return 1;
		}

	}
}