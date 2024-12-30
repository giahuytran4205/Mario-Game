#pragma once
#include "BulletBill.hpp"
#include "Enemy.hpp"

class EnemiesBillBlaster : public Enemy {
private:
	const int RANGE_ACTIVE = 250;

private:
	Mario& m_mario;
	int m_fireCD;
	int m_curFireCD;

public:
	EnemiesBillBlaster(Mario& mario, Object* parent = nullptr);
	~EnemiesBillBlaster() = default;

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void hit(bool isDestroy);
	void fire(const Direction& direction);
};

