#pragma once
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>

class Coroutine {
public:
	struct promise_type {
		Coroutine get_return_object() {
			return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};

private:
	std::coroutine_handle<promise_type> handle_;

public:
	explicit Coroutine(std::coroutine_handle<promise_type> handle);
	Coroutine(const Coroutine&) = delete;
	Coroutine(Coroutine&& other) noexcept;
	~Coroutine();

	Coroutine& operator=(const Coroutine&) = delete;
	Coroutine& operator=(Coroutine&& other);

	void resume();
	bool done() const;
};