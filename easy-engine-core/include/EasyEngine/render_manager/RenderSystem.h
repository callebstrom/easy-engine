#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#pragma once

#include <EasyEngine/ecs/ISystem.h>
#include <EasyEngine/event_manager/IObserver.h>
#include <EasyEngine/render_manager/IRenderManager.h>

namespace easy_engine {

	namespace render_manager {
		class RenderSystem : public ecs::ISystem, public event_manager::IObserver {
		public:
			RenderSystem(
				std::shared_ptr<event_manager::EventManager> event_manager,
				std::shared_ptr<render_manager::IRenderManager> render_manager
			);
			~RenderSystem();

			virtual void Update(float dt) override;
			virtual void OnEvent(event_manager::Event event) override;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !RENDER_SYSTEM_H