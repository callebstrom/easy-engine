#pragma once

#include <thread>

#include <RenderManagerOpenGL.h>
#include <SceneManager.h>
#include <Renderable3D.h>
#include <Scene3DOpenGL.h>
#include <ManagerLocator.h>

namespace easy_engine {
	namespace scene_manager {
		class SceneManagerOpenGL : public SceneManager {
			public:
				void RenderScene();
				void CreateScene(std::string name);
		};
	}
}