#include <EasyEngine/eepch.h>
#include <EasyEngine/scene_manager/SceneGraph3D.h>

namespace easy_engine {
	namespace scene_manager {
		void SceneGraph3D::traverse() {
			for (Node* node : this->root->nodes) {
				if (node->node_type == NODE_TYPE::RENDERABLE) {
					event_manager::Event render_event = event_manager::Event();
					resource::Renderable* renderable = static_cast<RenderableNode*>(node)->renderable_;
					render_event.data = renderable;
					render_event.event_type = event_manager::EventType::k3DObjectRenderable;
					render_event.message_id = atoi(renderable->name.c_str());
					ManagerLocator::event_manager->DispatchAsync(render_event);
				}
			}

			event_manager::Event post_render_event = event_manager::Event();
			post_render_event.event_type = event_manager::EventType::kPostRender;
			ManagerLocator::event_manager->DispatchAsync(post_render_event);
		};
	}
}
