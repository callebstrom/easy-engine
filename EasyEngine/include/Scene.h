#pragma once

#include <Renderable.h>
#include <vector>
#include <iostream>
#include <map>

namespace easy_engine {
	namespace scene_manager {
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
