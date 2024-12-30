#pragma once
#include "Item.hpp"
#include "Physics2D.hpp"

class FireFlower : public Item {
private:

public:
	FireFlower(Object* parent = nullptr);
	~FireFlower();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void appear() override;
};