#pragma once

#include <RootNode.h>
#include <SceneManager.h>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class SceneGraph {
				public:
					virtual void traverse() = 0;
					RootNode* root;
			};
		}
	}
}