#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <EasyEngine/resource/Renderable.h>
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
			void Add(resource::Renderable* renderable);
			std::vector<resource::Renderable*> Get();
			std::map<std::string, resource::Renderable*> renderable_map; // Map containing renderables as value and reference as key
		protected:
			SceneGraph* scene_graph_;
		};
	}
}

#endif
