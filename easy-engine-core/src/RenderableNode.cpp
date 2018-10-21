#include <RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {
		RenderableNode::RenderableNode(renderable::Renderable* renderable) : Node(parent, nodes) {
			this->renderable_ = renderable;
			this->node_type = NODE_TYPE::RENDERABLE;
		}
	}
}
