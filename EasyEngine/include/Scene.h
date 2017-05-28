#pragma once

#include <Renderable.h>
#include <vector>
#include <iostream>
#include <map>

#ifndef SCENE_H
namespace easy_engine {
	namespace scene {
		class Scene {
			public:
				std::string name;
				float size;
				void Add(renderable::Renderable* renderable);
				std::vector<renderable::Renderable*> Get();
				std::map<std::string, renderable::Renderable*> renderable_map; // Map containing renderables as value and reference as key
		};
	}
}
#endif // !SCENE_MANAGER_3D_H
