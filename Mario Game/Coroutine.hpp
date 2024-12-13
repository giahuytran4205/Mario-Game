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


public:
	coroutine_handle<promise_type> handle_;
	float m_duration = 0;

public:
	explicit Coroutine(std::coroutine_handle<promise_type> handle);
	Coroutine(const Coroutine&) = delete;
	Coroutine(Coroutine&& other) noexcept;
	~Coroutine();

	Coroutine& operator=(const Coroutine&) = delete;
	Coroutine& operator=(Coroutine&& other);

	void resume();
	bool done() const;
	void setDuration(float duration);
	float getDuration();
};

struct WaitForMiliseconds {
	explicit WaitForMiliseconds(float aDuration) {
		duration = aDuration;
	}

	sf::Clock clock;
	float duration;
	bool await_ready() {
		cout << clock.getElapsedTime().asMilliseconds() << '\n';
		return clock.getElapsedTime().asMilliseconds() >= duration;
	}
	void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) {
		handle.promise().duration = 1000;
	}
	void await_resume() {}
};