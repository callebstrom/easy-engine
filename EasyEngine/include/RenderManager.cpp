#include "RenderManager.h"

namespace easy_engine {
	namespace render_manager {

		// Push a vector of renderables onto the queue
		void RenderManager::RenderQueuePush(std::vector<renderable::Renderable*> renderable)
		{
			for(auto &element : renderable)
				this->render_queue.push_back(element);
		}

		// Push single renderables onto the queue
		void RenderManager::RenderQueuePush(renderable::Renderable* renderable)
		{
			this->render_queue.push_back(renderable);
		}
	}
}