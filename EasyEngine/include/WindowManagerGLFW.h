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
				void RegisterMousePositionCallback(GLFWcursorposfun callback);
				void RegisterMouseCallback(GLFWmousebuttonfun callback);
				void RegisterKeyboardCallback(GLFWkeyfun callback);
				void RegisterResizeCallback(void* func);
				void CreateWindow(configuration::WindowConfiguration_t* configuration);
				void SwapBuffers();
				~WindowManagerGLFW();
			private:
				static logger::Logger* log;
				GLFWwindow* window_;
				void UpdateFpsCounter();
		};
	}
}