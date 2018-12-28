#include <EasyEngine/eepch.h>
#include <EasyEngine/scene_manager/SceneManager.h>
#include <EasyEngine/renderable/Renderable3D.h>

namespace easy_engine {
	namespace scene_manager {
		void SceneManager::Add(renderable::Renderable* renderable, std::string scene_name)
		{
			Scene* scene = this->scene_map.at(scene_name);
			scene->Add(renderable);
		}

		void SceneManager::Add(renderable::Renderable * renderable)
		{
			this->current_scene->Add(renderable);
		}

		Scene* SceneManager::GetCurrentScene()
		{
			return this->current_scene;
		}

		void SceneManager::SetCurrentScene(std::string scene_name)
		{
			this->current_scene = this->scene_map.at(scene_name);
		}

		SceneManager::SceneManager() {
			this->scene_map = std::map<std::string, Scene*>();
		}
	}
}