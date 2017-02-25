#include "Renderable3D.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

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

		float* Renderable3D::GetVertexNormalArray() {
			return nullptr;
		}

		std::string *** Renderable3D::GetFaces()
		{
			return nullptr;
		}
	}
}