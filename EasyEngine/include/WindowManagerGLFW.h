#pragma once

#include <glfw3.h>

#include <WindowManager.h>

#ifndef WINDOW_MANAGER_H

namespace easy_engine {
	namespace window_manager {

		class WindowManager : public WindowManager {
			public:
				void registerMousePositionCallback(GLFWcursorposfun callback);
				void registerMouseCallback(GLFWmousebuttonfun callback);
				void registerKeyboardCallback(GLFWkeyfun callback);
				void createWindow();
		};
	}
}
#endif // !WINDOW_MANAGER_H