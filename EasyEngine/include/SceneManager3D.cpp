#include "SceneManager3D.h"

namespace easy_engine {
	namespace scene_manager {
		SceneManager3D::SceneManager3D() {
			this->scene_map = std::map<std::string, scene::Scene3D*>();
		}

		void SceneManager3D::CreateScene(std::string name) {
			scene::Scene3D* scene_3d = new scene::Scene3D();
			this->scene_map.insert(std::make_pair(name, scene_3d));
		}

		scene::Scene3D* SceneManager3D::GetCurrentScene() {
			return nullptr;
		}
	}
}
