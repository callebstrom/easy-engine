#include "SceneManager.h"

namespace easy_engine {
	namespace scene_manager {
		void SceneManager::Add(renderable::Renderable * renderable, std::string scene_name)
		{
		}

		void SceneManager::Add(renderable::Renderable * renderable)
		{
			
		}

		scene::Scene* SceneManager::GetCurrentScene()
		{
			return this->current_scene;
		}

		void SceneManager::SetCurrentScene(std::string scene_name)
		{
			this->current_scene = this->scene_map.at(scene_name);
		}

		SceneManager::SceneManager() {
			this->scene_map = std::map<std::string, scene::Scene*>();
		}
	}
}