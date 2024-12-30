#pragma once
#include "Enemy.hpp"

class BuzzyShell : public Enemy {
private:
	bool m_isLaunch;

public:
	BuzzyShell(Object* parent = nullptr);
	~BuzzyShell();

	void onCollisionEnter(Collision& col, const Direction& side);
	void update() override;
	void die() override;
};