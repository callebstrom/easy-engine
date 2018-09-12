#pragma once

#include <Renderable.h>
#include <Eigen\Core>

namespace easy_engine {
	namespace renderable {

		class Renderable3D : public Renderable {

			typedef float*(*func_ptr_t)(Renderable3D*);

			public:
				Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices_;
				// Eigen::MatrixX3f vertices_;
				Eigen::MatrixX2f texture_vertices_;
				Eigen::MatrixX3f vertex_normals_;
				std::vector<ushort_t> faces_;

				uint32_t vertex_count;

				float* GetVertexArray();
				float* GetTextureVertexArray();
				float* GetVertexNormalArray(func_ptr_t compute_normals_func);
				void Draw(func_ptr_t draw_func);

				std::vector<ushort_t> vertex_indices_;
				std::vector<ushort_t> uv_indices_;
				std::vector<ushort_t> normal_indices_;
		};
	}
}