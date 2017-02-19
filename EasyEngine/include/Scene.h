#pragma once

#include <Renderable.h>

#include <map>

#ifndef SCENE_H
namespace easy_engine {
	namespace scene {
		class Scene {
			public:
				std::string name;
				float size;
			protected:
				std::map<std::string, renderable::Renderable> renderable_map; // Map containing renderables as value and reference as key
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
