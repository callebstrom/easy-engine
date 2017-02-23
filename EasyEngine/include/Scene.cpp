#include "Scene.h"

void easy_engine::scene::Scene::Add(renderable::Renderable * renderable)
{
	this->renderable_map.insert(std::make_pair(renderable->name, renderable));
}
