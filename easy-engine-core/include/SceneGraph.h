#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H
#pragma once

#include <RootNode.h>
#include <SceneManager.h>

namespace easy_engine {
	namespace scene_manager {
		class DLLEXPORT SceneGraph {
			public:
				virtual void traverse() = 0;
				RootNode* root;
		};
	}
}

#endif