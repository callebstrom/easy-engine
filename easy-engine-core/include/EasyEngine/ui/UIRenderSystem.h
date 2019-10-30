#ifndef UI_RENDER_SYSTEM_H
#define UI_RENDER_SYSTEM_H
#pragma once

#include <EasyEngine/ecs/ISystem.h>

namespace easy_engine {

	namespace ui {
		class IUIRenderManager;
	}

	namespace ui {
		class UIRenderSystem : public ecs::ISystem {
		public:
			UIRenderSystem(std::shared_ptr<ui::IUIRenderManager> ui_render_manager);
			virtual void Update(float dt) override;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !UI_RENDER_SYSTEM_H