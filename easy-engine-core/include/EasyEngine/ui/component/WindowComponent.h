#ifndef UI_WINDOW_COMPONENT
#define UI_WINDOW_COMPONENT
#pragma once

#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {
	namespace ui {
		namespace component {

			class EASY_ENGINE_API WindowComponent : public ecs::component::Component {
			public:
				std::string title;
				int width;
				int height;
			};
		}
	}
}

#endif // !UI_WINDOW_COMPONENT

