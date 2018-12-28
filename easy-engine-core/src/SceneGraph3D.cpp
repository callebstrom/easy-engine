#include <EasyEngine/scene_manager/SceneGraph3D.h>

namespace easy_engine {
	namespace scene_manager {
		void SceneGraph3D::traverse() {
			for (Node* node : this->root->nodes) {
				if (node->node_type == NODE_TYPE::RENDERABLE) {
					ManagerLocator::render_manager->Render(static_cast<RenderableNode*>(node)->renderable_);
				}
			}
		};
	}
}
