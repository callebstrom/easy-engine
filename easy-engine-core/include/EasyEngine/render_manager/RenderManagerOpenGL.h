#ifndef RENDER_MANAGER_OPEN_GL_H
#define RENDER_MANAGER_OPEN_GL_H
#pragma once

#include <EasyEngine/event_manager/IObserver.h>
#include <EasyEngine/render_manager/RenderManager.h>
#include <EasyEngine/resource/Mesh.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {

	namespace render_manager {

		class EASY_ENGINE_API RenderManagerOpenGL : public RenderManager, public event_manager::IObserver {

		public:
			RenderManagerOpenGL(configuration::RenderConfiguration_t* rc);
			~RenderManagerOpenGL();
			RenderManagerOpenGL(const RenderManagerOpenGL& other);
			RenderManagerOpenGL& operator=(RenderManagerOpenGL other);

			void Render(resource::Mesh* mesh, Eigen::Matrix4f model_matrix) override;
			void UpdateCameraAngle(double x, double y) override;
			void OnEvent(event_manager::Event event) override;

		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}
#endif // !RENDER_MANAGER_OPEN_GL_H
