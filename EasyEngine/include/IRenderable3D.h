#pragma once
#include <string>

#ifndef I_RENDERABLE_3D_h
namespace easy_engine {
	namespace renderable {
		typedef std::string group_name;

		template <class T>

		/*
			Interface that defines the mandatory functions for a rendable 3D object. 
			Only objects implementing IRenderable3D can be put on a RenderManager3D queue
		 */
		class IRenderable3D {
		public:
			virtual T* GetVertices() = 0;
			virtual T* GetTextureVertices() = 0;
			virtual T* GetVertexNormals() = 0;
			virtual std::string*** GetFaces() = 0;
		};
	}
}
#endif