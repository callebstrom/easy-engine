#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {

	namespace resource {
		class Mesh;
	}

	namespace ecs {
		namespace component {
			class MeshComponent : public Component {
			public:
				resource::Mesh* renderable;
			};
		}
	}
}



#endif // !MESH_COMPONENT_H

