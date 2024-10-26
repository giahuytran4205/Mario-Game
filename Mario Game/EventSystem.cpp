#include "EventSystem.hpp"

EventSystem* EventSystem::m_instance = nullptr;

EventSystem::EventSystem(RenderWindow& window) : m_window(window) {
	if (!m_instance) {
		m_instance = this;
	}
}

EventSystem::~EventSystem() {

}

void EventSystem::handleEvents() {
	Event event;
	while (m_window.pollEvent(event)) {
		sendEvent(event);
	}
}

void EventSystem::addListener(IEventListener* listener) {
	m_listeners.push_back(listener);
}

void EventSystem::sendEvent(const Event& event) {
	for (auto& listener : m_listeners) {
		listener->handleEvent(event);
	}
}