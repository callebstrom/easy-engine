#include <RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			RenderableNode::RenderableNode(renderable::Renderable* renderable) : Node(parent, nodes) {
				this->renderable_ = renderable;
			}
		}
	}
}
