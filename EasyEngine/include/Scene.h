#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <Renderable.h>
#include <SceneGraph.h>
#include <vector>
#include <iostream>
#include <map>

class SceneGraph;

namespace easy_engine {
	namespace scene_manager {
		class Scene {
			friend class SceneManager;
			public:
				std::string name;
				float size;
				void Add(renderable::Renderable* renderable);
				std::vector<renderable::Renderable*> Get();
				std::map<std::string, renderable::Renderable*> renderable_map; // Map containing renderables as value and reference as key
			protected:
				SceneGraph* scene_graph_;
			private:
				static logger::Logger* log;
		};
	}
}

#endif
