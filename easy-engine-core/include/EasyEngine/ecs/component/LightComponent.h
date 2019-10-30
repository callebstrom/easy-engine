#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/resource/Light.h>

namespace easy_engine {

	namespace ecs {
		namespace component {
			struct EASY_ENGINE_API LightComponent : public Component {
				LightComponent(resource::Light* light)
					: light(light) {}

				resource::Light* light;
			};
		}
	}
}



#endif // !LIGHT_COMPONENT_H

