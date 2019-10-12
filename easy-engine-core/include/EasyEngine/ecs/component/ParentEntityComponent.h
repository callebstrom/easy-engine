#ifndef PARENT_ENTITY_COMPONENT_H
#define PARENT_ENTITY_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/ecs/entity/Entity.h>

namespace easy_engine {
	namespace ecs {
		namespace component {
			class EASY_ENGINE_API ParentEntityComponent : public Component {
			public:
				EntityID id;
			};
		}
	}
}



#endif // !PARENT_ENTITY_COMPONENT_H

