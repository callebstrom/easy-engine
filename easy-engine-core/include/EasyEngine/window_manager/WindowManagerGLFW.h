#pragma once

#include <EasyEngine/window_manager/IWindowManager.h>
#include <EasyEngine/event_manager/IObserver.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

#include <GL/glfw3.h>

namespace easy_engine {

	namespace event_manager {
		class EventManager;
	}

	namespace input_manager {
		class InputManager;
	}

	namespace window_manager {

		class EASY_ENGINE_API WindowManagerGLFW : public IWindowManager, public event_manager::IObserver {
		public:
			WindowManagerGLFW(
				std::shared_ptr<event_manager::EventManager> event_manager,
				std::shared_ptr<input_manager::InputManager> input_manager
			);
			~WindowManagerGLFW();

			void IWindowManager::CreateWindowEE(configuration::WindowConfiguration_t* configuration) override;
			void OnEvent(event_manager::Event event) override;
			void CloseWindow() override;
			void SwapBuffers() override;
			void* GetWindow() override;
			void Init() {
				glfwInit();
			}
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
			std::shared_ptr<event_manager::EventManager> event_manager_;
			std::shared_ptr<input_manager::InputManager> input_manager_;
		};
	}
}