#include "CoroutineManager.hpp"
#include "GameManager.hpp"

CoroutineManager* CoroutineManager::m_instance = nullptr;

CoroutineManager::CoroutineManager() {
	if (!m_instance)
		m_instance = this;
}

CoroutineManager::~CoroutineManager() {}

CoroutineManager* CoroutineManager::getInstance() {
	return m_instance;
}

void CoroutineManager::addCoroutine(Coroutine&& coroutine) {
	m_coroutines.push_back(move(coroutine.handle_));
}

void CoroutineManager::update() {
	for (auto& coroutine : m_coroutines) {
		float& duration = coroutine.promise().duration;
		duration -= deltaTime.asMilliseconds();
		duration = max(duration, 0.0f);
		if (duration == 0 && !coroutine.done()) {
			coroutine.resume();
		}
	}

	m_coroutines.erase(
		std::remove_if(m_coroutines.begin(), m_coroutines.end(),
			[](auto& c) { return c.done(); }),
		m_coroutines.end());
}