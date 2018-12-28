#pragma once

#include <GL/glfw3.h>

#include <EasyEngine/window_manager/WindowManager.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/window_manager/InputCallbackGLFW.h>

namespace easy_engine {
	namespace window_manager {

		class EASY_ENGINE_API WindowManagerGLFW : public WindowManager {
			public:
				void RegisterMousePositionCallback(GLFWcursorposfun callback);
				void RegisterMouseCallback(GLFWmousebuttonfun callback);
				void RegisterKeyboardCallback(GLFWkeyfun callback);
				void RegisterResizeCallback(void* func);
				void WindowManager::CreateWindowEE(configuration::WindowConfiguration_t* configuration) override;
				void SwapBuffers();
				~WindowManagerGLFW();
			private:
				GLFWwindow* window_;
				void UpdateFpsCounter();
		};
	}
}