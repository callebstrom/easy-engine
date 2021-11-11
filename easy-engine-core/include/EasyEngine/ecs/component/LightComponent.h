#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>
#include <EasyEngine/resource/Light.h>

namespace easy_engine {

	namespace ecs {
		namespace component {
			class EASY_ENGINE_API LightComponent : public Component {
			public:
				LightComponent(resource::PointLight point_light)
					: point_light_(std::make_optional(point_light)), directional_light_(std::nullopt) {}
				
				LightComponent(resource::DirectionalLight directional_light)
					: directional_light_(std::make_optional(directional_light)), point_light_(std::nullopt) {}

				auto GetPointLight()->std::optional<resource::PointLight>;
				auto GetDirectionalLight()->std::optional<resource::DirectionalLight>;

			private:
				std::optional<resource::PointLight> point_light_;
				std::optional<resource::DirectionalLight> directional_light_;
			};
		}
	}
}



#endif // !LIGHT_COMPONENT_H

