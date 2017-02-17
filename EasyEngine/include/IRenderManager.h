#pragma once
#include <Eigen\Core>
#include <IRenderable.h>
#include <vector>

#ifndef I_RENDER_MANAGER_H

namespace easy_engine {
	namespace render_manager {
		class IRenderManager {
			public:
				virtual void Render() = 0;
				virtual void RenderQueuePush() = 0;
				virtual void RenderQueuePop() = 0;
			private:
				std::vector<renderable::IRenderable> render_queue;
		};
	}
}
#endif // !I_RENDER_MANAGER_H