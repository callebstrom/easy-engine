#pragma once

namespace easy_engine {

	namespace render_manager {
		class RenderManagerOpenGL;
	}

	namespace input_manager {

		enum Key;

		class EASY_ENGINE_API InputManager {
		public:
			void HandleMouseEvent(int button, int modifier, double x, double y);
			void HandeKeyboardEvent(int key, int scancode, int action, int modifiers);
			void PollEvents();
		private:
			std::set<Key> repeated_keys_;
		};
	}
}