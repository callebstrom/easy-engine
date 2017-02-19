#pragma once

#include <RenderManagerOpenGL.h>
#include <SceneManager.h>
#include <Scene3D.h>
#include <Renderable3DOpenGL.h>

#ifndef SCENE_MANAGER_3D_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager3D : public SceneManager<scene::Scene3D> {
			public:
				SceneManager3D();
				void CreateScene(std::string);
				scene::Scene3D* GetCurrentScene();
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
