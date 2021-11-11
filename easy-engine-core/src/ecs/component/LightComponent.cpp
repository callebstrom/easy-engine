#include <EasyEngine/eepch.h>
#include <EasyEngine/ecs/component/LightComponent.h>

namespace easy_engine {
	namespace ecs {
		namespace component {
			auto LightComponent::GetPointLight() -> std::optional<resource::PointLight>	{
				return point_light_;
			}

			auto LightComponent::GetDirectionalLight() -> std::optional<resource::DirectionalLight> {
				return directional_light_;
			}
		}
	}
}