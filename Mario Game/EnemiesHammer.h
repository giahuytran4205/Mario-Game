#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Enemy.hpp"

class EnemiesHammer : public Enemy
{
	enum State {
		NONE,
		INIT,
		FALL,
	};
private:
	bool mIsActive{ false };
	State mState{ NONE };
	Vector2f mPosSrc;
	Vector2f mPosTarget;
	float mXTagret{ 0 };
public:
	EnemiesHammer(Object* parent = nullptr);
	~EnemiesHammer() = default;
	void setActive(
		const Vector2f& posSrc,
		const Vector2f& posTarget
	);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

