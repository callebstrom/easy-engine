#include <Scene.h>
#include <Renderable3D.h>
#include <iostream>

#include <boost\foreach.hpp>

namespace easy_engine{
	namespace scene {
		void Scene::Add(renderable::Renderable* renderable)
		{
			this->renderable_map.insert(renderable->name, renderable);
		}

		std::vector<renderable::Renderable*> Scene::Get()
		{
			std::vector<renderable::Renderable *> renderable_vector;
			
			BOOST_FOREACH(auto pair, this->renderable_map)
				renderable_vector.push_back(pair.second);

			return renderable_vector;
		}
	}
}
