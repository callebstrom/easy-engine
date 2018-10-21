#include "..\include\Node.h"

namespace easy_engine {
	namespace scene_manager {
		Node::Node(Node* parent, std::vector<Node*> nodes) {
			this->parent = parent;
			this->nodes = nodes;
		}
	}
}
