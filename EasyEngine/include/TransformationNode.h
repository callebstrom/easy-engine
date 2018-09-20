#ifndef TRANSFORMATION_NODE_H
#define TRANSFORMATION_NODE_H
#pragma once

#include <Node.h>
#include <Eigen\Core>

namespace easy_engine {
	namespace scene_manager {
		class TransformationNode : public Node {
		public:
			Eigen::Matrix4f transformation_;
		};
	}
}

#endif // !TRANSFORMATION_NODE_H
