#include "..\include\Node.h"

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			Node::Node() {

			}

			Node::Node(Node * parent, Node * left, Node * right) {
				this->parent = parent;
				this->left = left;
				this->right = right;
			}
		}
	}
}
