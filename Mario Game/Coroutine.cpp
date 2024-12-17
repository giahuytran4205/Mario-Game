#include "Coroutine.hpp"
#include "CoroutineManager.hpp"

Coroutine::Coroutine(std::coroutine_handle<promise_type> handle) : handle_(handle) {
	
}

Coroutine::Coroutine(Coroutine&& other) noexcept : handle_(other.handle_) {
	other.handle_ = nullptr;
}

Coroutine::~Coroutine() {
	if (handle_) handle_.destroy();
}

Coroutine& Coroutine::operator=(Coroutine&& other) {
	if (this != &other) {
		if (handle_) handle_.destroy();
		handle_ = other.handle_;
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

coroutine_handle<Coroutine::promise_type>& Coroutine::getHandle() {
	return handle_;
}