#pragma once
#include "EnemiesHammer.h"

class EnemiesHammerBro : public Enemy
{
	Mario& mMario;
	bool mIsActive{ false };
	const int RANGE_ACTIVE = 250;
	const int RANGE_MARIO = 250;

	std::vector<EnemiesHammer*> mHammer;
	int mMinActiveX, mMaxActiveX;
	int mCnt{ 0 };
public:
	EnemiesHammerBro(Mario& mario, const Vector2f pos, 
		Object* parent);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

