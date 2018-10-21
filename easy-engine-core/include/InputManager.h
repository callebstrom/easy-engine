#pragma once

#include <Common.h>
#include <GL/glfw3.h>

namespace easy_engine {
	namespace input_manager {
		class DLLEXPORT InputManager {
			public:
				void HandleMousePosUpdate(double x, double y);
				void HandleMouseButtonPress(int button, int modifier);
				void HandleMouseButtonRelease(int button, int modifier);
				void PollEvents();
			private:
				static logger::Logger* log;
		};
	}
}