#include <Scene.h>
#include <Renderable3D.h>
#include <RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {

		logger::Logger* Scene::log = new logger::Logger("Scene");

		void Scene::Add(renderable::Renderable* renderable) {
			log->debug("Adding renderable to scene");
			this->scene_graph_->root->nodes.push_back(new RenderableNode(renderable));
		}

		std::vector<renderable::Renderable*> Scene::Get() {
			std::vector<renderable::Renderable *> renderable_vector;
			
			for (auto pair : this->renderable_map)
				renderable_vector.push_back(pair.second);

			return renderable_vector;
		}
	}
}
