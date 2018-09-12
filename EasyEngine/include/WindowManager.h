#pragma once

#include <WindowConfiguration.h>

namespace easy_engine {
	namespace window_manager {
		class WindowManager {

			typedef void(*func_type)(void);

			public:
				virtual void createWindow(configuration::WindowConfiguration_t* configuration) = 0;
		};
	}
}