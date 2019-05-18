#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H
#pragma once

#include <EasyEngine/scene_manager/RootNode.h>
#include <EasyEngine/scene_manager/SceneManager.h>

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API SceneGraph {
		public:
			virtual void traverse() = 0;
			RootNode* root;
		};
	}
}

#endif