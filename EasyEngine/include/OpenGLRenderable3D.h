#pragma once

#include <glfw3.h>
#include <Eigen\Core>
#include <IRenderable3D.h>

#ifndef OPEN_GL_RENDERABLE_3D_H

namespace easy_engine {
	namespace renderable {
		class OpenGLRenderable3D : virtual IRenderable3D<GLfloat> {
			GLfloat* GetVertices();
			GLfloat* GetTextureVertices();
			GLfloat* GetVertexNormals();
			std::string*** GetFaces();
		};
	}
}
#endif // !OPEN_GL_RENDERABLE_3D_H
