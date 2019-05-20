#ifndef RENDERABLE_NODE_H
#define RENDERABLE_NODE_H
#pragma once

#include <EasyEngine/scene_manager/Node.h>
#include <EasyEngine/resource/Renderable.h>

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API RenderableNode : public Node {
		public:
			RenderableNode(resource::Renderable* renderable);
			resource::Renderable* renderable_;
		};
	}
}
#endif // !RENDERABLE_NODE_H
