#include <WindowManagerGLFW.h>

namespace easy_engine {
	namespace window_manager {

		logger::Logger* WindowManagerGLFW::log = new logger::Logger("WindowManagerGLFW");

		void WindowManagerGLFW::RegisterMousePositionCallback(GLFWcursorposfun callback) {
			glfwSetCursorPosCallback(this->window_, callback);
		}

		void WindowManagerGLFW::RegisterMouseCallback(GLFWmousebuttonfun callback) {
		
		}

		void WindowManagerGLFW::RegisterKeyboardCallback(GLFWkeyfun callback) {
		
		}

		void WindowManagerGLFW::RegisterResizeCallback(void* func) {
			// glfwSetWindowSizeCallback(func);
		}
		
		void WindowManagerGLFW::CreateWindow(configuration::WindowConfiguration_t* configuration) {

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			int resX = atoi(configuration->Get(configuration::WindowConfigurationParams::WIDTH).c_str());
			int resY = atoi(configuration->Get(configuration::WindowConfigurationParams::HEIGHT).c_str());

			// this->window_ = glfwCreateWindow(resX, resY, "Easy	Engine", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
			this->window_ = glfwCreateWindow(resX, resY, "EasyEngine", nullptr, nullptr); // Windowed

			if (!this->window_) {
				glfwTerminate();
				log->fatal("Failed to create window");
			}

			glfwMakeContextCurrent(this->window_);

			GLenum error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwSetInputMode(this->window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (ManagerLocator::input_manager != NULL) {
				// Forward input events to the InputManager
				InputCallbackGLFW::input_manager = ManagerLocator::input_manager;
				RegisterMousePositionCallback(&InputCallbackGLFW::MousePosCallback);
				RegisterMouseCallback(&InputCallbackGLFW::MouseButtonCallback);
				RegisterKeyboardCallback(&InputCallbackGLFW::KeyboardCallback);

				// TODO create the actual window using GLFW
			} else {
				log->warning("No input manager set");
			}
		};

		void WindowManagerGLFW::SwapBuffers() {
			glfwSwapBuffers(this->window_);
		}

		void WindowManagerGLFW::UpdateFpsCounter() {
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

		WindowManagerGLFW::~WindowManagerGLFW() {
			glfwTerminate();
		}
	}
}