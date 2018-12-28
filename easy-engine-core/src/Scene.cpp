#include <EasyEngine/eepch.h>
#include <EasyEngine/scene_manager/Scene.h>
#include <EasyEngine/scene_manager/RenderableNode.h>
#include <EasyEngine/renderable/Renderable3D.h>

namespace easy_engine {
	namespace scene_manager {
		
		void Scene::Add(renderable::Renderable* renderable) {
			EE_CORE_TRACE("Adding renderable to scene");
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
