#pragma once

#include <ISceneManager.h>
#include <map>

#ifndef SCENE_MANAGER_H
namespace easy_engine {
	namespace scene_manager {
		template <class T>
		class SceneManager : public virtual ISceneManager {
			protected:
				scene::Scene current_scene;
				std::map<std::string, T*> scene_map;
		};
	}
}
#endif // !SCENE_MANAGER_H
