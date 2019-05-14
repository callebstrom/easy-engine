#ifndef NODE_H
#define NODE_H
#pragma once

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API Node {
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
