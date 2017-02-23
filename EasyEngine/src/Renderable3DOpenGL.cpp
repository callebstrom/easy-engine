#include "Renderable3DOpenGL.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

namespace easy_engine {
	namespace renderable {
		GLfloat* Renderable3DOpenGL::GetVertexArray() {

			int rows = this->vertices_.rows();
			int cols = this->vertices_.cols();
			GLfloat *vertex_array = new GLfloat[rows * cols];

			int index = 0;
			for (int i = 0; i < rows; i++) {
				for (int x = 0; x < cols; x++) {
					vertex_array[index] = this->vertices_(i, x);
					index++;
				}
			}

			return vertex_array;
		}

		void Renderable3DOpenGL::GetTextureVertexArray(GLfloat* texture_vertex_array) {

		}

		void Renderable3DOpenGL::GetVertexNormalArray(GLfloat* vertex_normal_array) {

		}

		std::string *** Renderable3DOpenGL::GetFaces()
		{
			return nullptr;
		}
	}
}