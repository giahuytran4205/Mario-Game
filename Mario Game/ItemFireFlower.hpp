#pragma once

#include "Random.hpp"
#include "Enemy.hpp"
#include "Mario.hpp"
class ItemFireFlower : public Enemy
{
	static const int TIME_RAISING = 600;

private:
	bool mIsActive{ false };
	Vector2f mPosSrc;
public:
	ItemFireFlower(Object* parent = nullptr);
	~ItemFireFlower() = default;
	void setActive(
		const Vector2f& posSrc
	);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

