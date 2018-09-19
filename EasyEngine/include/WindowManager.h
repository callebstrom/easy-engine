#pragma once

#include <WindowConfiguration.h>
#include <Common.h>

namespace easy_engine {
	namespace window_manager {
		class WindowManager {

			typedef void(*func_type)(void);

			public:
				virtual void CreateWindow(configuration::WindowConfiguration_t* configuration) = 0;
				virtual void SwapBuffers() = 0;
		};
	}
}