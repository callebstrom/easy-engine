#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {

	namespace resource {
		class Material;
	}

	namespace ecs {
		namespace component {
			class EASY_ENGINE_API MaterialComponent : public Component {
			public:
				std::vector<resource::Material*> materials;
			};
		}
	}
}



#endif // !MESH_COMPONENT_H

