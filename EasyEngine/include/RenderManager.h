#pragma once

#include <vector>
#include <Renderable.h>
#include <RenderConfiguration.h>

#ifndef RENDER_MANAGER_H

namespace easy_engine {
	namespace render_manager {
		class RenderManager {
			public:
				void RenderQueuePush(renderable::Renderable* renderable);
				void RenderManager::RenderQueuePush(std::vector<renderable::Renderable*> renderable);
				virtual void Render() = 0;
			protected:
				RenderConfiguration* render_config_;
				std::vector<renderable::Renderable*> render_queue;
				
		};
	}
}
#endif // !RENDER_MANAGER_H