#ifndef UI_WINDOW_COMPONENT
#define UI_WINDOW_COMPONENT
#pragma once

#include <EasyEngine/ui/component/IUIComponent.h>

namespace easy_engine {
	namespace ui {
		namespace component {
			class WindowComponent : public IUIComponent {
				IUIComponent* End() override;
			};
		}
	}
}

#endif // !UI_WINDOW_COMPONENT

