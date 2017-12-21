#include <Node.h>
#include <Renderable.h>

#pragma once

#ifndef SCENE_GRAPH_RENDERABLE_NODE
namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class RenderableNode : public Node {
			public:
				RenderableNode(renderable::Renderable* renderable);
			private:
				renderable::Renderable* renderable_;
			};
		}
	}
}
#endif // !SCENE_GRAPH_RENDERABLE_NODE
#pragma once
