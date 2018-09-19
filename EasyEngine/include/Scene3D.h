#pragma once

#include <Scene.h>
#include <Renderable3D.h>
#include <SceneGraph3D.h>
#include <RootNode.h>
#include <RenderableNode.h>

namespace easy_engine {
	namespace scene_manager {
		class Scene3D : public Scene {
			friend class SceneManager3D;
			public:
				Scene3D::Scene3D();
				void Add(renderable::Renderable3D* renderable);
			private:
				scene_graph::SceneGraph3D* scene_graph_;
		};
	}
}