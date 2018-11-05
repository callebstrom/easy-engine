#ifndef SCENE_GRAPH_3D_h
#define SCENE_GRAPH_3D_h
#pragma once

#include <Eigen/Core>
#include <EasyEngine/renderable/Renderable3D.h>
#include <EasyEngine/scene_manager/SceneGraph.h>
#include <EasyEngine/scene_manager/SceneManager3D.h>

namespace easy_engine {
	namespace scene_manager {
		class EASY_ENGINE_API SceneGraph3D : public SceneGraph {
		public:
			void traverse();
		private:
			Eigen::Matrix4f current_translation_;
			static logger::Logger* log;
		};
	}
}
#endif // !SCENE_GRAPH_3D_h
