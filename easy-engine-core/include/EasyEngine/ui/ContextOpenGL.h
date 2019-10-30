#ifndef UI_CONTEXT_OPEN_GL
#define UI_CONTEXT_OPEN_GL
#pragma once

#include <GL/glfw3.h>

#include <EasyEngine/ui/IContext.h>

namespace easy_engine {
	namespace ui {
		class ContextOpenGL : public IContext {
		public:
			ContextOpenGL(GLFWwindow* window);
			auto CreateUIWindow() -> Ref<component::WindowComponent> override;
			auto End() -> void override;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !UI_CONTEXT_OPEN_GL