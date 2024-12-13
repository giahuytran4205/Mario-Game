#pragma once
#include "Coroutine.hpp"
#include <vector>

class CoroutineManager {
private:
	static CoroutineManager* m_instance;
	std::vector<std::coroutine_handle<Coroutine::promise_type>> m_coroutines;

public:
	CoroutineManager();
	~CoroutineManager();

	static CoroutineManager* getInstance();
	void addCoroutine(Coroutine&& coroutine);
	void update();
};