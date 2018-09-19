#include "SceneGraph3D.h"
#include <typeinfo>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			void SceneGraph3D::traverse() {
				for (Node* node : this->root->nodes) {
					const char* node_type = typeid(node).name();

					if (node_type == "RenderableNode") {
						ManagerLocator::render_manager->Render(static_cast<RenderableNode*>(node)->renderable_);
					}
				}
			};
		}
	}
}
