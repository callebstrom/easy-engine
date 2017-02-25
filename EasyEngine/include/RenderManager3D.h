#pragma once

#include <RenderManager.h>
#include <Renderable3D.h>
#include <cstdlib>

#ifndef RENDER_MANAGER_3D_H
namespace easy_engine {
	namespace render_manager {
		class RenderManager3D : public RenderManager {
			public:
				virtual void Render() = 0;
		};
	}
}
#endif // !RENDER_MANAGER_3D_H