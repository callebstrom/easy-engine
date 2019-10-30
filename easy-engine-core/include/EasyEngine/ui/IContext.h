#ifndef UI_CONTEXT
#define UI_CONTEXT
#pragma once

#include <EasyEngine/ui/component/WindowComponent.h>

namespace easy_engine {
	namespace ui {
		class IContext {
		public:
			auto virtual CreateUIWindow() -> Ref<component::WindowComponent> = 0;
			auto virtual End() -> void = 0;
		private:
			friend class component::WindowComponent;
		};

	}
}

#endif // !UI_CONTEXT

