#include <EasyEngine/eepch.h>
#include <EasyEngine/event_manager/EventManager.h>

void easy_engine::event_manager::EventManager::Subscribe(EventType event_type, IObserver* observer, Callback callback) {
	EventDelegate delegate = EventDelegate(observer, callback);
	
	this->event_delegates_[event_type].push_back(delegate);
}


void easy_engine::event_manager::EventManager::Dispatch(Event event) {
	this->event_buffer_[event.event_type].push_back(event);
}

void easy_engine::event_manager::EventManager::ConsumeEventBuffer(EventType eventType) {
	for (auto const& event : this->event_buffer_[eventType]) {
		EE_CORE_TRACE("Consuming event buffer");
	}
}

 