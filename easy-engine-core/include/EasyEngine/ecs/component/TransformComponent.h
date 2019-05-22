#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#pragma once

#include <Eigen/Core>

namespace easy_engine {
	namespace component {
		class TransformComponent : public Component {
		public:
			Eigen::Matrix4f position;
			Eigen::Matrix4f rotation;
			Eigen::Matrix4f scale;
		};
	}
}

#endif // !TRANSFORM_COMPONENT_H

