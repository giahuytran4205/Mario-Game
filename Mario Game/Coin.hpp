#pragma once
#include "Item.hpp"

class Coin : public Item {
private:

public:
	Coin(Object* parent = nullptr);
	Coin(float x, float y, Object* parent = nullptr);
	Coin(const Vector2f& pos, Object* parent = nullptr);
	~Coin();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
};