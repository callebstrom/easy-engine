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
			class EASY_ENGINE_API MeshComponent : public Component {
			public:
				std::vector<resource::Mesh*>* sub_meshes = new std::vector<resource::Mesh*>();
			};
		}
	}
}



#endif // !MESH_COMPONENT_H

