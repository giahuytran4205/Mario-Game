#pragma once
#include <random>
#include <ctime>
using namespace std;

template<typename T>
T randRange(T min, T max) {
	std::random_device rd;
	std::mt19937 gen(rd());

	if constexpr (is_integral<T>::value) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(gen);
	}
	std::uniform_real_distribution<double> dist(min, max);

	return dist(gen);
}

bool randByProbability(float rate);