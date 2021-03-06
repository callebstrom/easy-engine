#pragma once
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <EasyEngine/event_manager/Event.h>
#include <EasyEngine/event_manager/IObserver.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {
	namespace event_manager {

		class EASY_ENGINE_API EventManager {

			class EventDelegate {
			public:
				IObserver* observer;
				Callback callback;
				EventDelegate(IObserver* observer_, Callback callback_) {
					observer = observer_;
					callback = callback_;
				}
			};

		public:
			void Subscribe(EventType event_type, IObserver* observer);
			void Unsubscribe(EventType event_type, IObserver* observer);
			void DispatchAsync(Event event);
			void Dispatch(Event event);
			void ConsumeEventBuffer(EventType eventType);

		private:
			std::map<EventType, std::vector<EventDelegate>> event_delegates_;
			std::map<EventType, std::queue<Event>> event_buffer_; // to be consumed during given phases of the game loop
		};

	}
}

#endif // !EVENT_MANAGER_H
