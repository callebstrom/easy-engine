#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#pragma once

#include <vector>

#include <Eigen\Core>

#include <Renderable.h>
#include <Renderable3D.h>
#include <RenderConfiguration.h>
#include <Common.h>

namespace easy_engine {
	namespace render_manager {
		class DLLEXPORT RenderManager {
		public:
			virtual void Render(renderable::Renderable* renderable) = 0;
		protected:
			configuration::RenderConfiguration_t* render_config_;
			std::vector<renderable::Renderable*> render_queue;

		};
	}
}
#endif // !RENDER_MANAGER_H
