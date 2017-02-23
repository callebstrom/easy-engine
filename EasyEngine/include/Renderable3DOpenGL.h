#pragma once

#include <glfw3.h>
#include <Eigen\Core>
#include <IRenderable3D.h>
#include <Renderable3D.h>

#ifndef RENDERABLE_3D_OPEN_GL_H

namespace easy_engine {
	namespace renderable {
		class Renderable3DOpenGL : public Renderable3D, public IRenderable3D<GLfloat> {
			public:
				GLfloat* GetVertexArray();
				void GetTextureVertexArray(GLfloat* texture_vertex_array);
				void GetVertexNormalArray(GLfloat* vertex_normal_array);
				std::string*** GetFaces();
		};
	}
}
#endif // !OPEN_GL_RENDERABLE_3D_H
