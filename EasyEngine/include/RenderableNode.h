#pragma once

#include <Node.h>
#include <Renderable.h>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class RenderableNode : public Node {
				public:
					RenderableNode(renderable::Renderable* renderable);
					renderable::Renderable* renderable_;
			};
		}
	}
}