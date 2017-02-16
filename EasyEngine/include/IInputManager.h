#pragma once

#ifndef I_INPUT_MANAGER
namespace easy_engine {
	namespace input_manager {
		class IInputManager {
			public:
				virtual void GetPressedKeys() = 0;
		};
	}
}
#endif // !I_INPUT_MANAGER
