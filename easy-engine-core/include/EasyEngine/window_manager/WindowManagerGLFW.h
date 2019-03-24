#pragma once

#include <GL/glfw3.h>

#include <EasyEngine/window_manager/WindowManager.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/Logger.h>
#include <EasyEngine/window_manager/InputCallbackGLFW.h>
#include <EasyEngine/event_manager/IObserver.h>

namespace easy_engine {
	namespace window_manager {

		class EASY_ENGINE_API WindowManagerGLFW : public WindowManager, public event_manager::IObserver {
			public:
				void RegisterMousePositionCallback(GLFWcursorposfun callback);
				void RegisterMouseCallback(GLFWmousebuttonfun callback);
				void RegisterKeyboardCallback(GLFWkeyfun callback);
				void RegisterResizeCallback(void* func);
				void WindowManager::CreateWindowEE(configuration::WindowConfiguration_t* configuration) override;
				void OnPostRender(event_manager::Event event);
				void OnNodeRenderable(event_manager::Event event) override;
				void CloseWindowEE() override;
				void SwapBuffers() override;
				WindowManagerGLFW();
				~WindowManagerGLFW();
			private:
				GLFWwindow* window_;
				void UpdateFpsCounter();
		};
	}
}