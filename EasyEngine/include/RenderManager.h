#pragma once

#include <vector>
#include <Renderable.h>
#include <Renderable3D.h>
#include <RenderConfiguration.h>
#include <Eigen\Core>

#ifndef RENDER_MANAGER_H

namespace easy_engine {
	namespace render_manager {
		class RenderManager {
			public:
				void RenderQueuePush(renderable::Renderable* renderable);
				void RenderManager::RenderQueuePush(std::vector<renderable::Renderable*> renderable);
				virtual void Render() = 0;
				void ComputeNormals(renderable::Renderable3D* renderable);
			protected:
				configuration::RenderConfiguration_t* render_config_;
				std::vector<renderable::Renderable*> render_queue;
				
		};
	}
}
#endif // !RENDER_MANAGER_H