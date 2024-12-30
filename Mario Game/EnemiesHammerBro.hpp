#pragma once
#include "Hammer.hpp"
#include "Enemy.hpp"

class EnemiesHammerBro : public Enemy {
private:
	const int RANGE_ACTIVE = 250;
	const int RANGE_MARIO = 250;
	enum State {
		WALK,
		FIRE
	};

private:
	Mario& m_mario;
	bool m_isActive = false;
	int m_minActiveX, m_maxActiveX;
	int m_fireCD;
	int m_curFireCD;

	Coroutine spawnHammer();

public:
	EnemiesHammerBro(Mario& mario, Object* parent = nullptr);
	EnemiesHammerBro(Mario& mario, const Vector2f& pos, Object* parent = nullptr);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
	void fire();
	void die();
};

