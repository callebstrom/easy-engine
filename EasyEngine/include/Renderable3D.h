#pragma once

#include <Renderable.h>
#include <Eigen\Core>

#ifndef RENDERABLE_3D_H
namespace easy_engine {
	namespace renderable {

		

		class Renderable3D : public Renderable {

			typedef void(*func_ptr_t)(Renderable3D*);

			public:
				Eigen::MatrixX3f vertices_;
				Eigen::MatrixX2f texture_vertices_;
				Eigen::MatrixX3f vertex_normals_;
				std::vector<ushort_t> faces_;

				uint32_t vertex_count;

				float* GetVertexArray();
				float* GetTextureVertexArray();
				float* GetVertexNormalArray(func_ptr_t compute_normals_func);
		};
	}
}
#endif // !RENDERABLE_3D_H