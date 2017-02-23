#pragma once

#include <Scene.h>
#include <ISceneManager.h>
#include <map>

#ifndef SCENE_MANAGER_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager : public virtual ISceneManager {
			public: 
				void Add(renderable::Renderable* renderable, std::string scene_name);
				void Add(renderable::Renderable* renderable);
				scene::Scene* GetCurrentScene();
				void SetCurrentScene(std::string scene_name);
				SceneManager();

			protected:
				scene::Scene* current_scene;
				std::map<std::string, scene::Scene*> scene_map;
		};
	}
}
#endif // !SCENE_MANAGER_H
