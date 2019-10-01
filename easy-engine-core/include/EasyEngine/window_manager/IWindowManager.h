#pragma once

#include <EasyEngine/configuration/WindowConfiguration.h>

namespace easy_engine {
	namespace window_manager {
		class EASY_ENGINE_API IWindowManager {

			typedef void(*func_type)(void);

		public:
			virtual void CreateWindowEE(configuration::WindowConfiguration_t* configuration) = 0;
			virtual void CloseWindow() = 0;
			virtual void SwapBuffers() = 0;
			virtual void* GetWindow() = 0;
		};
	}
}