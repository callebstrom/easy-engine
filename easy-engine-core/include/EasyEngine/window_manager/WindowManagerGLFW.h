#pragma once

#include <EasyEngine/window_manager/WindowManager.h>
#include <EasyEngine/ManagerLocator.h>
#include <EasyEngine/event_manager/IObserver.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {
	namespace window_manager {

		class EASY_ENGINE_API WindowManagerGLFW : public WindowManager, public event_manager::IObserver {
		public:
			WindowManagerGLFW();
			~WindowManagerGLFW();

			void WindowManager::CreateWindowEE(configuration::WindowConfiguration_t* configuration) override;
			void OnEvent(event_manager::Event event) override;
			void CloseWindowEE() override;
			void SwapBuffers() override;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}