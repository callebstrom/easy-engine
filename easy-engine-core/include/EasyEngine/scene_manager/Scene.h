#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <EasyEngine/renderable/Renderable.h>
#include <EasyEngine/scene_manager/SceneGraph.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

class SceneGraph;

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API Scene {
			friend class SceneManager;
			public:
				std::string name;
				float size;
				void Add(renderable::Renderable* renderable);
				std::vector<renderable::Renderable*> Get();
				std::map<std::string, renderable::Renderable*> renderable_map; // Map containing renderables as value and reference as key
			protected:
				SceneGraph* scene_graph_;
		};
	}
}

#endif
