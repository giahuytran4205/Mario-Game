#include "EventSystem.hpp"

IEventListener::IEventListener() {
	EventSystem::getInstance()->addListener(this);
}

IEventListener::~IEventListener() {
	EventSystem::getInstance()->removeListener(this);
}

EventSystem* EventSystem::m_instance = nullptr;
vector<IEventListener*> EventSystem::m_listeners;

EventSystem::EventSystem(RenderWindow& window) : m_window(window) {
	if (!m_instance) {
		m_instance = this;
	}
}

EventSystem::~EventSystem() {

}

EventSystem* EventSystem::getInstance() {
	return m_instance;
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

void EventSystem::removeListener(IEventListener* listener) {
	auto it = find(m_listeners.begin(), m_listeners.end(), listener);
	if (it != m_listeners.end())
		m_listeners.erase(it);
}

void EventSystem::sendEvent(const Event& event) {
	for (int i = 0; i < m_listeners.size(); i++)
		m_listeners[i]->handleEvent(event);
}