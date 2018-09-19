#pragma once

#include <Node.h>
#include <Eigen\Core>

namespace easy_engine {
	namespace scene_manager {
		namespace scene_graph {
			class TransformationNode : public Node {
				public:
					Eigen::Matrix4f transformation_;
			};
		}
	}
}
