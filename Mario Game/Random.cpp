#include "Random.hpp"

int randByProbability(const vector<int>& weights) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<> dist(weights.begin(), weights.end());

	return dist(gen);
}