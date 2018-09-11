#pragma once

#include <thread>

#include <RenderManagerOpenGL.h>
#include <SceneManager.h>
#include <Renderable3D.h>
#include <Scene3DOpenGL.h>
#include <ManagerLocator.h>

#ifndef SCENE_MANAGER_OPEN_GL_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManagerOpenGL : public SceneManager {
			public:
				void RenderScene();
				void CreateScene(std::string name);
		};
	}
}
#endif // !SCENE_MANAGER_3D_OPEN_GL_H
