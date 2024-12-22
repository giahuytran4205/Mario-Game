#pragma once
#include "Coroutine.hpp"
#include <vector>

class CoroutineManager {
private:
	static CoroutineManager* m_instance;
	std::vector<Coroutine> m_coroutines;

public:
	CoroutineManager();
	~CoroutineManager();

	static CoroutineManager* getInstance();
	void addCoroutine(Coroutine&& coroutine);
	void update();
};