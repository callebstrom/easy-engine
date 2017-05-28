#pragma once

#include <Renderable.h>
#include <Eigen\Core>

#ifndef RENDERABLE_3D_H
namespace easy_engine {
	namespace renderable {
		class Renderable3D : public Renderable {
			public:
				Eigen::MatrixX3f vertices_;
				Eigen::MatrixX2cf texture_vertices_;
				Eigen::MatrixX3cf vertex_normals_;
				std::string*** faces_;

				uint32_t vertex_count;

				float* GetVertexArray();
				float* GetTextureVertexArray();
				float* GetVertexNormalArray();
				std::string*** GetFaces();
		};
	}
}
#endif // !RENDERABLE_3D_H