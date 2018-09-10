#include "RenderManager.h"

namespace easy_engine {
	namespace render_manager {
		// Push single renderables onto the queue
		void RenderManager::AddRenderable(renderable::Renderable* renderable) {
			this->render_queue.push_back(renderable);
		}
	}
}