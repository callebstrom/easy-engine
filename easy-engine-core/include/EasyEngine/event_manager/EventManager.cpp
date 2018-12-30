#include <EasyEngine/eepch.h>
#include <EasyEngine/event_manager/EventManager.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>

void easy_engine::event_manager::EventManager::Subscribe(EventType event_type, IObserver* observer, Callback callback) {
	EventDelegate delegate = EventDelegate(observer, callback);
	this->event_delegates_[event_type].push_back(delegate);
}

void easy_engine::event_manager::EventManager::Dispatch(Event event) {
	this->event_buffer_[event.event_type].push(event);
}

void easy_engine::event_manager::EventManager::ConsumeEventBuffer(EventType eventType) {
	while (!this->event_buffer_[eventType].empty()) {
		auto const& event = this->event_buffer_[eventType].front();
		for (auto delegate : this->event_delegates_[eventType]) {
			(((render_manager::RenderManagerOpenGL*)delegate.observer)->*delegate.callback)(event);
		}

		this->event_buffer_[eventType].pop();
	}
}

 