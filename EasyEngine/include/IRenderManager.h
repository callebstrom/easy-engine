#pragma once
#include <Eigen\Core>
#include <vector>

#ifndef I_RENDER_MANAGER_H

namespace easy_engine {
	namespace render_manager {
		class IRenderManager {
			public:
				virtual void Render() = 0;
				virtual void RenderQueuePush() = 0;
		};
	}
}
#endif // !I_RENDER_MANAGER_H