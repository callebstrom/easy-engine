#pragma once

#include <EasyEngine/configuration/WindowConfiguration.h>
#include <EasyEngine/Common.h>

namespace easy_engine {
	namespace window_manager {
		class EASY_ENGINE_API WindowManager {

			typedef void(*func_type)(void);

			public:
				virtual void CreateWindow(configuration::WindowConfiguration_t* configuration) = 0;
				virtual void SwapBuffers() = 0;
		};
	}
}