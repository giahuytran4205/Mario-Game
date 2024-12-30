#pragma once
#include "Enemy.hpp"
#include "Mario.hpp"

class EnemiesPiranhaPlant: public Enemy {
private:
	int m_timeAtk;
	int m_atkCD;
	int m_curAtkCD;

public:
    EnemiesPiranhaPlant(Object* parent = nullptr);
    ~EnemiesPiranhaPlant() = default;

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void die() override;
	void attack();
};

