#pragma once
#include <string>

#ifndef I_RENDERABLE_3D_H
namespace easy_engine {
	namespace renderable {
		typedef std::string group_name;

		/**
		 *	Interface that defines the mandatory functions for a rendable 3D object. 
		 *	Only objects implementing IRenderable3D can be put on a RenderManager3D queue via the SceneManager3D
		**/
		template <class T>
		class IRenderable3D {
			public:
				virtual T* GetVertexArray() = 0;
				virtual void GetTextureVertexArray(T* texture_vertex_array) = 0;
				virtual void GetVertexNormalArray(T* vetex_normal_array) = 0;
				virtual std::string*** GetFaces() = 0;
		};
	}
}
#endif // !I_RENDERABLE_3D_H