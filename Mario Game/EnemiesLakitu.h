#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Mario.hpp"
#include "Enemy.hpp"

#include "EnemiesSpiny.h"

class EnemiesLakitu : public Enemy
{
	enum State {
		RUNING_LEFT,
		RUNING_RIGHT,
	};

	static const int MAX_SPINY = 50;
private:
	float m_speed = 0.1;
	int mTimeUpdate{ 0 };
	Mario& mMario;

	bool mIsDone{ false };
	bool mIsActive{ false };
	const int RANGE_ACTIVE = 500;
	const int RANGE_MARIO = 250;
	int mMinActiveX, mMaxActiveX;
	State mState = RUNING_LEFT;
	bool mIsStep{ false };
	bool m_isDead;

	/*std::vector<std::shared_ptr<EnemiesSpiny>> mSpinys;*/
	std::vector<EnemiesSpiny*> mSpinys;
public:
	EnemiesLakitu(Mario& mario, const Vector2f pos, 
		Object* parent);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

