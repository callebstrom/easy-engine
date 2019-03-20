#include <EasyEngine/eepch.h>
#include <EasyEngine/event_manager/EventManager.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>

void easy_engine::event_manager::EventManager::Subscribe(EventType event_type, IObserver* observer, Callback callback) {
	EventDelegate delegate = EventDelegate(observer, callback);
	this->event_delegates_[event_type].push_back(delegate);
}

void easy_engine::event_manager::EventManager::Unsubscribe(EventType event_type, IObserver * observer, Callback callback) {
	auto delegates = this->event_delegates_[event_type];
	for (int i = 0; i < delegates.size(); i++) {
		auto delegate = delegates[i];
		if (delegate.observer == observer && delegate.callback) {
			delegates.erase(delegates.begin() + i);
		}
	}
}

void easy_engine::event_manager::EventManager::Dispatch(Event event) {
	this->event_buffer_[event.event_type].push(event);
}

void easy_engine::event_manager::EventManager::ConsumeEventBuffer(EventType event_type) {
	while (!this->event_buffer_[event_type].empty()) {
		auto const& event = this->event_buffer_[event_type].front();
		for (auto delegate : this->event_delegates_[event_type]) {
			(((IObserver*)delegate.observer)->*delegate.callback)(event);
		}

		this->event_buffer_[event_type].pop();
	}
}

 