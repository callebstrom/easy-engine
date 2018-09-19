#pragma once

#include <Eigen/Core>
#include <Renderable3D.h>
#include <SceneGraph.h>
#include <SceneManager3D.h>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class SceneGraph3D : public SceneGraph {
				public:
					void traverse();
				private:
					Eigen::Matrix4f current_translation_;
			};
		}
	}
}