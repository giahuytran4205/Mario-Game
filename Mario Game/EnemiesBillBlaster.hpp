#pragma once
#include "EnemiesBillBlasterBullet.hpp"
class EnemiesBillBlaster : public Enemy
{
	Mario& mMario;
	bool mIsActive{ false };
	const int RANGE_ACTIVE = 250;

	std::vector<EnemiesBillBlasterBullet*> mBullet;

	Vector2f mPos{ -1, -1 };

public:
	EnemiesBillBlaster(Mario& mario, Object* parent);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

