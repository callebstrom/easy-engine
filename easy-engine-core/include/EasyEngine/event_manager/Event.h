#pragma once
#ifndef EVENT_H
#define EVENT_H

namespace easy_engine {
	namespace event_manager {
		enum class EventType {
			GlobalTick,
			_3DObjectRenderable,
			_3DPostRender,
			KeyPressed,
			KeyReleased,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseMoved,
		};

		struct Event {
			EventType event_type;
			int message_id;
			void* data;
		};
	}
}

#endif // !EVENT_H
