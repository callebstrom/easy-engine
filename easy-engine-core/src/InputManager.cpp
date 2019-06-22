#include <EasyEngine/eepch.h>
#include <GL/glfw3.h>
#include <EasyEngine/input_manager/InputManager.h>
#include <EasyEngine/input_manager/KeyboardEvent.h>
#include <EasyEngine/ManagerLocator.h>

namespace easy_engine {
	namespace input_manager {

		void InputManager::HandleMouseEvent(int button, int modifier, double x, double y)
		{
		}

		void InputManager::HandeKeyboardEvent(int key_, int scancode, int action, int modifiers)
		{

			Key key = (Key)key_;

			// Repeat is handled internally
			if (action == GLFW_REPEAT) return;

			// TODO action GLFW_REPEAT is only sent for latest button, i.e. need to build support for repeating multiple keys
			auto event = easy_engine::event_manager::Event(easy_engine::event_manager::EventType::Keyboard);

			auto event_data = new KeyboardEvent();
			event_data->key = key;
			event_data->modifiers = modifiers;

			switch (action) {
			case GLFW_PRESS:
				event_data->action = Action::kPressed;
				this->repeated_keys_.insert(key);
				break;
			case GLFW_RELEASE:
				event_data->action = Action::kReleased;
				this->repeated_keys_.erase(key);
				break;
			}

			event.data = event_data;
			ManagerLocator::event_manager->Dispatch(event);
		}
		void InputManager::PollEvents() {
			// TODO this should support modifiers. Perhaps store a tuple in repeated_keys_ set?
			for (auto repeated_key : this->repeated_keys_) {
				auto event = easy_engine::event_manager::Event(easy_engine::event_manager::EventType::Keyboard);
				event.data = new KeyboardEvent(repeated_key, 0, Action::kPressed);
				ManagerLocator::event_manager->Dispatch(event);
			}
			glfwPollEvents();
		}

	}
}