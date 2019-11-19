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
				int buffer_size;
				int width;
				int height;

				TextAreaComponent(int width, int height, int buffer_size, std::string value)
					: height(height), width(width), buffer(new char[buffer_size]) {
					for (int i = 0; i < buffer_size; i++) {
						this->buffer[i] = '\0';
					}
					easy_engine::Replace(value, "\t", "  ");
					this->buffer_size = value.length();
					memcpy(this->buffer, value.c_str(), value.length());
				}
			};
		}
	}
}

#endif // !UI_TEXT_AREA_COMPONENT
