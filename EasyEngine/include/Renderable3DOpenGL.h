#pragma once

#include <glfw3.h>
#include <Eigen\Core>
#include <IRenderable3D.h>

#ifndef RENDERABLE_3D_OPEN_GL_H

namespace easy_engine {
	namespace renderable {
		class Renderable3DOpenGL : virtual IRenderable3D<GLfloat> {
			GLfloat* GetVertices();
			GLfloat* GetTextureVertices();
			GLfloat* GetVertexNormals();
			std::string*** GetFaces();
		};
	}
}
#endif // !OPEN_GL_RENDERABLE_3D_H
