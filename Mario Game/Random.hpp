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


class RandomQuestion {
public:
	enum Type{
		UNKNOW,
		COIN,
		MUSH_ROOM,
		FLOWER,
		STAR
	};
private:
	float _perCoin{ 20 }, _perMushroom{ 10 }, _perFlower{ 10 }, _perStar{ 10 };

public:
	RandomQuestion() = default;

	// Setters
	void setPerCoin(float perCoin) { _perCoin = perCoin; }
	void setPerMushroom(float perMushroom) { _perMushroom = perMushroom; }
	void setPerFlower(float perFlower) { _perFlower = perFlower; }
	void setPerStar(float perStar) { _perStar = perStar; }

	// Getters
	float getPerCoin() const { return _perCoin; }
	float getPerMushroom() const { return _perMushroom; }
	float getPerFlower() const { return _perFlower; }
	float getPerStar() const { return _perStar; }

	RandomQuestion::Type getRadomType() const {
		float totalPercent = _perCoin + _perMushroom + _perFlower + _perStar;

		if (totalPercent != 100.0f) {
            throw std::invalid_argument("Total percentage must be 100!");
		}
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.0f, 100.0f);

		float randomValue = dist(gen);

		if (randomValue <= _perCoin) {
			return RandomQuestion::COIN;
		}
		else if (randomValue <= _perCoin + _perMushroom) {
			return RandomQuestion::MUSH_ROOM;
		}
		else if (randomValue <= _perCoin + _perMushroom + _perFlower) {
			return RandomQuestion::FLOWER;
		}
		else {
			return RandomQuestion::STAR;
		}
	}
};


