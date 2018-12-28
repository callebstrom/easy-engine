#pragma once

#include <GL/glfw3.h>

#include <EasyEngine/Common.h>

namespace easy_engine {

	namespace render_manager {
		class RenderManagerOpenGL;
	}

	namespace input_manager {
		class EASY_ENGINE_API InputManager {
			public:
				void HandleMousePosUpdate(double x, double y);
				void HandleMouseButtonPress(int button, int modifier);
				void HandleMouseButtonRelease(int button, int modifier);
				void PollEvents();
		};
	}
}