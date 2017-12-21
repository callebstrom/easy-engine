#pragma once

#ifndef SCENE_GRAPH_NODE
namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class Node {
			protected:
				Node();
				Node(Node* parent, Node* left, Node* right);
				Node* left;
				Node* right;
				Node* parent;
			};
		}
	}
}
#endif // !SCENE_GRAPH_NODE
#pragma once
