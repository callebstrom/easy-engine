#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H
#pragma once

#include <EasyEngine/ui/component/IUIComponent.h>
#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {
	namespace ecs {
		namespace component {
			class EASY_ENGINE_API CanvasComponent : public Component {
			public:
				std::vector<ui::component::IUIComponent> ui_components;
			};
		}
	}
}



#endif // !UI_COMPONENT_H

