#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#pragma once

#include <Eigen/Core>

#include <EasyEngine/renderable/Renderable.h>
#include <EasyEngine/renderable/Renderable3D.h>
#include <EasyEngine/configuration/RenderConfiguration.h>

namespace easy_engine {
	namespace render_manager {
		class EASY_ENGINE_API RenderManager {
		public:
			virtual void Render(renderable::Renderable* renderable) = 0;
			virtual void UpdateCameraAngle(double x, double y) = 0;
			virtual ~RenderManager() = default;
		protected:
			configuration::RenderConfiguration_t* render_config_;
			std::vector<renderable::Renderable*> render_queue;
		};
	}
}
#endif // !RENDER_MANAGER_H
