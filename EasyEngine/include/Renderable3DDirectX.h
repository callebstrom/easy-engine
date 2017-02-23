#pragma once

#include <Eigen\Core>
#include <IRenderable3D.h>
#include <Renderable3D.h>

#ifndef RENDERABLE_3D_DIRECT_X_H

namespace easy_engine {
	namespace renderable {
		class Renderable3DDirectX : public Renderable3D, public virtual IRenderable3D<float> {
			float* GetVertexArray();
			float* GetTextureVertexArray();
			float* GetVertexNormalArray();
			std::string*** GetFaces();
		};
	}
}
#endif // !RENDERABLE_3D_DIRECT_X_H
