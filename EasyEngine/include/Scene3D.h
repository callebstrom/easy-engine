#ifndef SCENE3D_H
#define SCENE3D_H
#pragma once

#include <Scene.h>
#include <Renderable3D.h>
#include <RootNode.h>
#include <RenderableNode.h>
#include <SceneGraph3D.h>

namespace easy_engine {
	namespace scene_manager {
		
		class Scene3D : public Scene {
			friend class SceneManager3D;
			public:
				Scene3D::Scene3D();

			private:
				static logger::Logger* log;
		};
	}
}

#endif