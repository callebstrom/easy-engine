#ifndef RENDERABLE_NODE_H
#define RENDERABLE_NODE_H
#pragma once

#include <Node.h>
#include <Renderable.h>

namespace easy_engine {
	namespace scene_manager {
		class DLLEXPORT RenderableNode : public Node {
			public:
				RenderableNode(renderable::Renderable* renderable);
				renderable::Renderable* renderable_;
		};
	}
}
#endif // !RENDERABLE_NODE_H
