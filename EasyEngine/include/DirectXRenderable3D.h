#pragma once

#include <Eigen\Core>
#include <IRenderable3D.h>

#ifndef DIRECT_X_RENDERABLE_3D_H

namespace easy_engine {
	namespace renderable {
		class DirectXRenderable3D : virtual IRenderable3D<float> {
			float* GetVertices();
			float* GetTextureVertices();
			float* GetVertexNormals();
			std::string*** GetFaces();
		};
	}
}
#endif // !DIRECT_X_RENDERABLE_3D_H
