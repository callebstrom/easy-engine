#ifndef UI_RENDER_MANAGER_OPEN_GL_H
#define UI_RENDER_MANAGER_OPEN_GL_H
#pragma once

#include <EasyEngine/ui/IUIRenderManager.h>
#include <EasyEngine/event_manager/IObserver.h>
#include <EasyEngine/ecs/ISystem.h>

namespace easy_engine {

	namespace window_manager {
		class IWindowManager;
	}

	namespace event_manager {
		class EventManager;
	}

	namespace ui {
		class UIRenderManagerOpenGL : public IUIRenderManager, public event_manager::IObserver {
		public:
			UIRenderManagerOpenGL(
				std::shared_ptr<window_manager::IWindowManager> window_manager,
				std::shared_ptr<event_manager::EventManager> event_manager
			);
			void Render() override;
			void OnEvent(event_manager::Event event) override;
			void WindowBegin(std::string title, int height, int width) override;
			void WindowEnd() override;
		private:
			struct Impl;
			Impl* p_impl_;
		};
	}
}

#endif // !UI_RENDER_MANAGER_OPEN_GL_H