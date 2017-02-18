#pragma once

#include <ISceneManager.h>
#include <map>

#ifndef SCENE_MANAGER_H
namespace easy_engine {
	namespace scene_manager {
		class SceneManager : public virtual ISceneManager {
			protected:
				std::map<std::string, scene::Scene> scene_map;
				scene::Scene current_scene;
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
