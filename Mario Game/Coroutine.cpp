#include "Coroutine.hpp"
#include "CoroutineManager.hpp"

Coroutine::Coroutine(std::coroutine_handle<promise_type> handle) : handle_(handle) {
	m_duration = 0;
}

Coroutine::Coroutine(Coroutine&& other) noexcept : handle_(other.handle_), m_duration(other.m_duration) {
	other.handle_ = nullptr;
}

Coroutine::~Coroutine() {
	if (handle_) handle_.destroy();
}

Coroutine& Coroutine::operator=(Coroutine&& other) {
	if (this != &other) {
		if (handle_) handle_.destroy();
		handle_ = other.handle_;
		m_duration = other.m_duration;
		other.handle_ = nullptr;
	}
	return *this;
}

void Coroutine::resume() {
	if (handle_ && !handle_.done()) {
		handle_.resume();
	}
}

bool Coroutine::done() const {
	return handle_ ? handle_.done() : true;
}

void Coroutine::setDuration(float duration) {
	m_duration = duration;
}

float Coroutine::getDuration() {
	return m_duration;
}