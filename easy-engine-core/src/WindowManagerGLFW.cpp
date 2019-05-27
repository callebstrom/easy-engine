#include <EasyEngine/eepch.h>

#include <GL/glfw3.h>

#include <EasyEngine/window_manager/WindowManagerGLFW.h>
#include <EasyEngine/input_manager/InputManager.h>

struct InputCallbackGLFW {

	static void InputCallbackGLFW::MousePosCallback(GLFWwindow* window, double x, double y) {
		// Emit events
	};

	static void InputCallbackGLFW::MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
		// Emit events
	};

	static void InputCallbackGLFW::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
		// Emit events
	};
};

namespace easy_engine {
	namespace window_manager {

		struct WindowManagerGLFW::Impl {

			void UpdateFpsCounter() {
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

			GLFWwindow* window_;
		};

		void WindowManagerGLFW::CreateWindowEE(configuration::WindowConfiguration_t* configuration) {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			int resX = atoi(configuration->Get(configuration::WindowConfigurationParams::WIDTH).c_str());
			int resY = atoi(configuration->Get(configuration::WindowConfigurationParams::HEIGHT).c_str());

			// this->window_ = glfwCreateWindow(resX, resY, "Easy	Engine", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
			this->p_impl_->window_ = glfwCreateWindow(resX, resY, "EasyEngine", nullptr, nullptr); // Windowed

			if (!this->p_impl_->window_) {
				glfwTerminate();
				EE_CORE_CRITICAL("Failed to create window");
			}

			glfwMakeContextCurrent(this->p_impl_->window_);

			GLenum error = glGetError();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwSetInputMode(this->p_impl_->window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			glfwSetCursorPosCallback(this->p_impl_->window_, &InputCallbackGLFW::MousePosCallback);
			glfwSetMouseButtonCallback(this->p_impl_->window_, &InputCallbackGLFW::MouseButtonCallback);
			glfwSetKeyCallback(this->p_impl_->window_, &InputCallbackGLFW::KeyboardCallback);
		};

		void WindowManagerGLFW::CloseWindowEE() {
			glfwDestroyWindow(this->p_impl_->window_);
		}

		void WindowManagerGLFW::SwapBuffers() {
			glfwSwapBuffers(this->p_impl_->window_);
		}

		void WindowManagerGLFW::OnEvent(event_manager::Event event) {
			this->SwapBuffers();
		}

		WindowManagerGLFW::WindowManagerGLFW()
			: p_impl_(new Impl()) {
			ManagerLocator::event_manager->Subscribe(
				event_manager::EventType::_3DPostRender,
				this
			);
		}

		WindowManagerGLFW::~WindowManagerGLFW() {
			this->p_impl_.reset();
			glfwTerminate();
		}
	}
}