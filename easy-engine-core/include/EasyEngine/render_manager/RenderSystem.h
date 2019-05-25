#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#pragma once

#include <EasyEngine/ecs/ISystem.h>

namespace easy_engine {
	namespace render_manager {
		class RenderSystem : public ecs::ISystem {
		public:
			RenderSystem();
			~RenderSystem();

			virtual void Update(float dt) override;
		};
	}
}

#endif // !RENDER_SYSTEM_H