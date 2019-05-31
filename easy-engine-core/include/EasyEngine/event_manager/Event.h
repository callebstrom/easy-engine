#pragma once
#ifndef EVENT_H
#define EVENT_H

namespace easy_engine {
	namespace event_manager {
		enum class EventType {
			GlobalTick,
			_3DObjectRenderable,
			_3DPreRender,
			_3DPostRender,
			Keyboard,
			Mouse
		};

		struct Event {
			EventType event_type;
			int message_id;
			void* data;

			Event() = default;
			Event(EventType event_type)
				: event_type(event_type) {}
		};
	}
}

#endif // !EVENT_H
