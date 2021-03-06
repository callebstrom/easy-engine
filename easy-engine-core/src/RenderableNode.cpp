#include <EasyEngine/eepch.h>
#include <EasyEngine/scene_manager/RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {
		RenderableNode::RenderableNode(resource::Renderable* renderable) : Node(parent, nodes) {
			this->renderable_ = renderable;
			this->node_type = NODE_TYPE::RENDERABLE;
		}
	}
}
