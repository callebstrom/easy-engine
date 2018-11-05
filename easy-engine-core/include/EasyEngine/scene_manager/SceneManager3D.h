#ifndef SCENE_MANAGER_3D_H
#define SCENE_MANAGER_3D_H
#pragma once

#include <thread>

#include <EasyEngine/scene_manager/SceneManager.h>
#include <EasyEngine/scene_manager/Scene3D.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>
#include <EasyEngine/renderable/Renderable3D.h>
#include <EasyEngine/ManagerLocator.h>

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API SceneManager3D : public SceneManager {
		public:
			void RenderScene();
			void CreateScene(std::string name);

		private:
			static logger::Logger* log;
		};
	}
}
#endif // !SCENE_MANAGER_3D_H