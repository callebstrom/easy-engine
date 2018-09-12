#pragma once

#include <glfw3.h>

#include <WindowManager.h>
#include <ManagerLocator.h>
#include <Logger.h>
#include <InputCallbackGLFW.h>

namespace easy_engine {
	namespace window_manager {

		class WindowManagerGLFW : public WindowManager {
			public:
				void registerMousePositionCallback(GLFWcursorposfun callback);
				void registerMouseCallback(GLFWmousebuttonfun callback);
				void registerKeyboardCallback(GLFWkeyfun callback);
				void createWindow(configuration::WindowConfiguration_t* configuration);
			private:
				static logger::Logger* log;
				GLFWwindow* window_;
		};
	}
}