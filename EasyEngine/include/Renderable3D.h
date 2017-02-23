#pragma once

#include <Renderable.h>

#ifndef RENDERABLE_3D_H
namespace easy_engine {
	namespace renderable {
		class Renderable3D : public Renderable {
			public:
				Eigen::MatrixX3f vertices_;
				Eigen::MatrixX2cf texture_vertices_;
				Eigen::MatrixX3cf vertex_normals_;
				std::string*** faces_;
		};
	}
}
#endif // !RENDERABLE_3D_H