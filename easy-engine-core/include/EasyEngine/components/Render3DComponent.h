#ifndef RENDER_3D_COMPONENT_H
#define RENDER_3D_COMPONENT_H
#pragma once

#include <EasyEngine/renderable/Renderable3D.h>

namespace easy_engine {
	namespace component {
		class Render3DComponent {
		public:
			renderable::Renderable3D* renderable;
		};
	}
}



#endif // !RENDER_3D_COMPONENT_H

