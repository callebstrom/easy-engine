#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

#include <Renderable3D.h>
#include <RenderManagerOpenGL.h>

namespace easy_engine {
	namespace renderable {

		float* Renderable3D::GetVertexArray() {
			
			int rows = this->vertices_.rows();
			int cols = this->vertices_.cols();
			float* vertex_array = new float[rows * cols];

			int index = 0;
			for (int i = 0; i < rows; i++) {
				for (int x = 0; x < cols; x++) {
					vertex_array[index] = this->vertices_(i, x);
					index++;
				}
			}

			return vertex_array;
		}

		float* Renderable3D::GetTextureVertexArray() {
			return nullptr;
		}

		float* Renderable3D::GetVertexNormalArray(func_ptr_t compute_normals_func) {
			if (this->vertex_normals_.size == 0) {
				return nullptr;
			} else {
				compute_normals_func(this);
			}
		}
	}
}