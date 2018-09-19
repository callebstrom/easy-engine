#include "..\include\Node.h"

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			Node::Node(Node* parent, std::vector<Node*> nodes) {
				this->parent = parent;
				this->nodes = nodes;
			}
		}
	}
}
