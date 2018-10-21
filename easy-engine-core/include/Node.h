#ifndef NODE_H
#define NODE_H
#pragma once

#include <Common.h>

namespace easy_engine {
	namespace scene_manager {
		class DLLEXPORT Node {
			public:
				Node(Node* parent, std::vector<Node*> nodes);
				std::vector<Node*> nodes;
				Node* parent;
				int node_type;
		};

		enum NODE_TYPE : int {
			RENDERABLE
		};
	}
}

#endif // !NODE_H
