#pragma once
#include "Item.hpp"

class OneUpMushroom : public Item {
private:

public:
	OneUpMushroom(Object* parent = nullptr);
	OneUpMushroom(const Direction& direction, Object* parent = nullptr);
	~OneUpMushroom();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void appear() override;
};