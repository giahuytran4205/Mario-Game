#pragma once
#include "Random.hpp"
#include "Enemy.hpp"
#include "Mario.hpp"

class ItemAx : public Enemy
{
public:
	ItemAx(Object* parent = nullptr);
	~ItemAx() = default;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

