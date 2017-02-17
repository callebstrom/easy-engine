#include <RenderManagerOpenGL.h>
#include <RenderConfiguration.h>
#include <iostream>

namespace easy_engine {
	namespace render_manager {
		RenderManagerOpenGL::RenderManagerOpenGL(configuration::RenderConfiguration* rc) {
			this->render_config_ = rc;
			this->vertex_buffer_data_ = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f,  1.0f, 0.0f
			};
		};

		void RenderManagerOpenGL::Render() {
			std::cout << "rendering..";
			if (!glfwInit()) {
				throw std::runtime_error("Failed to initalize GLFW");
			}

			glfwWindowHint(GLFW_SAMPLES, atoi(this->render_config_->Get("antialiasing").c_str())); // Get AA level from configuration object
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
			GLFWwindow* window;

			int xRes = atoi(this->render_config_->Get("resolution.x").c_str()); // Get X resolution from configuration object
			int yRes = atoi(this->render_config_->Get("resolution.y").c_str()); // Get y resolution from configuration object
			window = glfwCreateWindow(xRes, yRes, "EasyEngine", NULL, NULL); // Open a window and create its OpenGL context
			if (window == NULL) {
				std::runtime_error("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.");
				getchar();
				glfwTerminate();
			}
			glfwMakeContextCurrent(window);

			// Initialize GLEW
			glewExperimental = true; // Needed for core profile
			if (glewInit() != GLEW_OK) {
				std::runtime_error("Failed to initalize GLEW");
				getchar();
				glfwTerminate();
			}

			// Ensure we can capture the escape key being pressed below
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

			// Set background color
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

			GLuint VertexArrayID;
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);

			// Create and compile our GLSL program from the shaders
			//GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

			glGenBuffers(1, &this->vertex_buffer_);
			glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_);

			do {

				// Clear the screen
				glClear(GL_COLOR_BUFFER_BIT);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_), &this->vertex_buffer_data_[0], GL_DYNAMIC_DRAW);

				// Use our shader
				// glUseProgram(programID);

				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);

				// Draw the array buffer using triangles !
				glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

				glDisableVertexAttribArray(0);

				// Swap buffers
				glfwSwapBuffers(window);
				glfwPollEvents();

				// Insert input  handler here
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
					this->vertex_buffer_data_[0] = this->vertex_buffer_data_[0] + 0.01f;
					this->vertex_buffer_data_[3] = this->vertex_buffer_data_[3] + 0.01f;
					this->vertex_buffer_data_[6] = this->vertex_buffer_data_[6] + 0.01f;
				}
				else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
					this->vertex_buffer_data_[0] = this->vertex_buffer_data_[0] - 0.01f;
					this->vertex_buffer_data_[3] = this->vertex_buffer_data_[3] - 0.01f;
					this->vertex_buffer_data_[6] = this->vertex_buffer_data_[6] - 0.01f;
				}

			} // Check if the ESC key was pressed or the window was closed
			while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
				glfwWindowShouldClose(window) == 0);

			// Cleanup VBO
			glDeleteBuffers(1, &this->vertex_buffer_);
			glDeleteVertexArrays(1, &VertexArrayID);
			// glDeleteProgram(programID);

			// Close OpenGL window and terminate GLFW
			glfwTerminate();
		};
	}
}