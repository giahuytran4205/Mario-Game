#pragma once
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include "SFML/System.hpp"
using namespace std;

class Coroutine {
public:
	struct promise_type {
		Coroutine get_return_object() {
			return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}
		float duration = 0;
		suspend_always initial_suspend() { return {}; }
		suspend_always final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};


private:
	coroutine_handle<promise_type> handle_;

public:
	explicit Coroutine(std::coroutine_handle<promise_type> handle);
	Coroutine(const Coroutine&) = delete;
	Coroutine(Coroutine&& other) noexcept;
	~Coroutine();

	Coroutine& operator=(const Coroutine&) = delete;
	Coroutine& operator=(Coroutine&& other);

	void resume();
	bool done() const;
	coroutine_handle<promise_type>& getHandle();
};

struct WaitForMiliseconds {
	float duration;

	explicit WaitForMiliseconds(float aDuration) {
		duration = aDuration;
	}

	bool await_ready() {
		return false;
	}

	void await_suspend(std::coroutine_handle<> handle) {
		coroutine_handle<Coroutine::promise_type>::from_address(handle.address()).promise().duration = duration;
	}

	float await_resume() { return duration; }
};