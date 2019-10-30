#ifndef UI_TEXT_AREA_COMPONENT
#define UI_TEXT_AREA_COMPONENT
#pragma once

#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {
	namespace ui {
		namespace component {

			class EASY_ENGINE_API TextAreaComponent : public ecs::component::Component {
			public:
				char* buffer;
				int buffer_length;
				int width;
				int height;
			};
		}
	}
}

#endif // !UI_TEXT_AREA_COMPONENT
