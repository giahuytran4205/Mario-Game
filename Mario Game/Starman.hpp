#pragma once
#include "Item.hpp"

class Starman : public Item {
private:

public:
	Starman(Object* parent = nullptr);
	Starman(const Direction& direction, Object* parent = nullptr);
	~Starman();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void appear() override;
};