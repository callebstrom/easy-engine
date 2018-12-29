#include <EasyEngine/eepch.h>
#include <EasyEngine/scene_manager/SceneGraph3D.h>

namespace easy_engine {
	namespace scene_manager {
		void SceneGraph3D::traverse() {
			for (Node* node : this->root->nodes) {
				if (node->node_type == NODE_TYPE::RENDERABLE) {

					event_manager::Event render_event = event_manager::Event();
					render_event.data = static_cast<RenderableNode*>(node)->renderable_;
					render_event.event_type = event_manager::EventType::NodeRenderable;
					ManagerLocator::event_manager->Dispatch(render_event);

					ManagerLocator::render_manager->Render(static_cast<RenderableNode*>(node)->renderable_);
				}
			}
		};
	}
}
