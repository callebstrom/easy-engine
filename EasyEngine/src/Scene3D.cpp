#pragma once

#include <Scene3D.h>
#include <typeinfo>

namespace easy_engine {
	namespace scene_manager {

		using scene_graph::RootNode;
		using scene_graph::Node;
		using scene_graph::RenderableNode;


		Scene3D::Scene3D() {
			this->scene_graph_ = new scene_graph::SceneGraph3D();
			this->scene_graph_->root = new scene_graph::RootNode(NULL, std::vector<Node*>());
		}

		void Scene3D::Add(renderable::Renderable3D * renderable) {
			// TODO generate scene graph node and add to scene graph
			this->scene_graph_->root->nodes.push_back(new RenderableNode(renderable));
		}
	}
}
