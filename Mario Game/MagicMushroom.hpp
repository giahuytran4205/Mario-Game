#pragma once
#include "Item.hpp"
#include "Collision.hpp"

class MagicMushroom : public Item {
private:

public:
	MagicMushroom(Object* parent = nullptr);
	MagicMushroom(const Direction& direction, Object* parent = nullptr);
	~MagicMushroom();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void appear() override;
};