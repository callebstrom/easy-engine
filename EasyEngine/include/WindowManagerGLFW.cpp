#include <WindowManagerGLFW.h>

namespace easy_engine {
	namespace window_manager {

		logger::Logger* WindowManagerGLFW::log = new logger::Logger("WindowManagerGLFW");

		void WindowManagerGLFW::registerMousePositionCallback(GLFWcursorposfun callback) {
			glfwSetCursorPosCallback(this->window_, callback);
		};

		void WindowManagerGLFW::registerMouseCallback(GLFWmousebuttonfun callback) {
		
		};

		void WindowManagerGLFW::registerKeyboardCallback(GLFWkeyfun callback) {
		
		};
		
		void WindowManagerGLFW::createWindow(configuration::WindowConfiguration_t* configuration) {
			if (ManagerLocator::input_manager != NULL) {
				InputCallbackGLFW::input_manager = ManagerLocator::input_manager;
				registerMousePositionCallback(&InputCallbackGLFW::MousePosCallback);
				registerMouseCallback(&InputCallbackGLFW::MouseButtonCallback);
				registerKeyboardCallback(&InputCallbackGLFW::KeyboardCallback);

				// TODO create the actual window using GLFW
			} else {
				log->warning("No input manager set");
			}
		};
	}
}