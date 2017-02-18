#pragma once

#include <IRenderable.h>
#include <Scene.h>

#ifndef I_SCENE_MANAGER_H
namespace easy_engine {
	namespace scene_manager {
		class ISceneManager {
			public:
				virtual void Add(renderable::IRenderable) = 0; // Add renderable object to scene
				virtual scene::Scene GetCurrentScene() = 0;
				virtual void LoadScene() = 0; // Loads current scene using a render manager inherting from IRenderManager
		};
	}
}
#endif // !I_SCENE_MANAGER_H
