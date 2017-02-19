#pragma once

#include <IRenderable3D.h>
#include <Scene.h>

#ifndef I_SCENE_MANAGER_H
namespace easy_engine {
	namespace scene_manager {
		class ISceneManager {
			public:
				virtual void Add(renderable::Renderable* renderable, std::string scene_name) = 0; // Adds renderable object to given scene_name
				virtual void Add(renderable::Renderable* renderable) = 0; // Adds renderable object to current scene
				virtual scene::Scene* GetCurrentScene() = 0;
				virtual void LoadScene() = 0; // Loads current scene using a render manager inherting from IRenderManager
				virtual void CreateScene(std::string name) = 0;
		};
	}
}
#endif // !I_SCENE_MANAGER_H
