#pragma once
#ifndef I_OBSERVER_H
#define I_OBSERVER_H

#include <EasyEngine/event_manager/Event.h>

namespace easy_engine {
	namespace event_manager {
		class EASY_ENGINE_API IObserver {
			friend class EventManager;
		};

	}
}

typedef void (easy_engine::event_manager::IObserver::* Callback)(easy_engine::event_manager::Event* event);

#endif // !I_OBSERVER_H
