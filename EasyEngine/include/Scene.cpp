#include <Scene.h>
#include <Renderable3D.h>
#include <RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {
		void Scene::Add(renderable::Renderable* renderable) {
			this->renderable_map.insert(std::pair<std::string, renderable::Renderable*>(renderable->name, renderable));
		}

		std::vector<renderable::Renderable*> Scene::Get() {
			std::vector<renderable::Renderable *> renderable_vector;
			
			for (auto pair : this->renderable_map)
				renderable_vector.push_back(pair.second);

			return renderable_vector;
		}
	}
}
