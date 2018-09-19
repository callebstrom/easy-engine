#pragma once

#include <Common.h>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class Node {
				public:
					Node(Node* parent, std::vector<Node*> nodes);
					std::vector<Node*> nodes;
					Node* parent;
			};
		}
	}
}
