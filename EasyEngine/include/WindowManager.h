#pragma once

#ifndef WINDOW_MANAGER_H

namespace easy_engine {
	namespace window_manager {
		class WindowManager {

			typedef void(*func_type)(void);

			public:
				virtual void registerMousePositionCallback(func_type func_ptr) = 0;
				virtual void registerMouseCallback(func_type func_ptr) = 0;
				virtual void registerKeyboardCallback(func_type func_ptr) = 0;
				virtual void createWindow() = 0;
		};
	}
}
#endif // !WINDOW_MANAGER_H