#pragma once

#include <typeinfo>
#include <EasyEngine/scene_manager/Scene3D.h>

namespace easy_engine {
	namespace scene_manager {

		logger::Logger* Scene3D::log = new logger::Logger("Scene3D");

		Scene3D::Scene3D() {
			this->scene_graph_ = new SceneGraph3D();
			this->scene_graph_->root = new RootNode(NULL, std::vector<Node*>());
		}
	}
}
