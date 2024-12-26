#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

class EnemiesSpiny : public Enemy
{
public:
	enum State {
		NONE,
		INIT,
		EGG,
		NORMAL,
	};
private:
	State mState{ NONE };
	bool mIsActive{ false };
	Vector2f mPosSrc;
	Vector2f mPosTarget;
	bool mIsRunRight{ true };
	bool m_onWall = false;
public:

	EnemiesSpiny(Object* parent = nullptr);
	~EnemiesSpiny() = default;
	void setActive(
		const Vector2f& posSrc,
		const Vector2f& posTarget,
		const bool isRunRight = true
	);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
	State getState();
};

