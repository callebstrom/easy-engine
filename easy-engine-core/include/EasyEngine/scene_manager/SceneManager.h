#ifndef SCENE_MANAGER
#define SCENE_MANAGER
#pragma once

#include <map>
#include <EasyEngine/scene_manager/Scene.h>

class Scene;

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API SceneManager {
			public: 
				void Add(renderable::Renderable* renderable, std::string scene_name);
				void Add(renderable::Renderable* renderable);
				Scene* GetCurrentScene();
				void SetCurrentScene(std::string scene_name);

				virtual void RenderScene() = 0;
				virtual void CreateScene(std::string name) = 0;

				SceneManager();
			protected:
				Scene* current_scene;
				std::map<std::string, Scene*> scene_map;
		};
	}
}
#endif SCENE_MANAGER