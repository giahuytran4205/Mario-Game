#pragma once

#include "Enemy.hpp"
#include "Mario.hpp"


class EnemiesBlooper : public Enemy
{
private:
	float m_speed = 0.1;
	int mTimeUpdate{ 0 };
	Mario& mMario;
	bool mIsActive{ false };
	const float RANGE_STEP = 30;
	const float RANGE_FLOW_MARIO= RANGE_STEP + 10;
public:
	EnemiesBlooper(Mario& mario, Object* parent);
	~EnemiesBlooper();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();

};

