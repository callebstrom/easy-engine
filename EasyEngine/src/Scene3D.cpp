#pragma once

#include <Scene3D.h>

#ifndef SCENE_3D_H
namespace easy_engine {
	namespace scene_manager {
		Scene3D::Scene3D() {
			this->scene_graph_ = new scene_graph::SceneGraph3D();
		}

		void Scene3D::Add(renderable::Renderable3D * renderable)
		{
			// TODO generate scene graph node and add to scene graph
			Scene::Add(renderable);
		}
	}
}
#endif // !SCENE_3D_H
