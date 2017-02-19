#pragma once

#include <Eigen\Core>
#include <IRenderable3D.h>

#ifndef RENDERABLE_3D_DIRECT_X_H

namespace easy_engine {
	namespace renderable {
		class Renderable3DDirectX : public IRenderable3D<float> {
			float* GetVertices();
			float* GetTextureVertices();
			float* GetVertexNormals();
			std::string*** GetFaces();
		};
	}
}
#endif // !RENDERABLE_3D_DIRECT_X_H
