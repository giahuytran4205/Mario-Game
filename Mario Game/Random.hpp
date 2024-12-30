#pragma once
#include <random>
#include <vector>
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

int randByProbability(const vector<int>& weights);

template<typename T, typename... TArgs>
T rand(T first, TArgs... other) {
	vector<T> v{ first, other... };
	int idx = randRange<int>(0, v.size() - 1);
	return v[idx];
}