#include "SceneGraph3D.h"

namespace easy_engine {
	namespace scene_manager {

		logger::Logger* SceneGraph3D::log = new logger::Logger("SceneGraph3D");

		void SceneGraph3D::traverse() {
			for (Node* node : this->root->nodes) {
				if (node->node_type == NODE_TYPE::RENDERABLE) {
					ManagerLocator::render_manager->Render(static_cast<RenderableNode*>(node)->renderable_);
				}
			}
		};
	}
}
