#ifndef I_UI_RENDER_MANAGER_OPEN_GL_H
#define I_UI_RENDER_MANAGER_OPEN_GL_H
#pragma once

namespace easy_engine {
	namespace ui {
		class IUIRenderManager {
		public:
			virtual auto Render() -> void = 0;
			virtual auto GetContext() -> void* = 0;
		};
	}
}

#endif // !I_UI_RENDER_MANAGER_OPEN_GL_H