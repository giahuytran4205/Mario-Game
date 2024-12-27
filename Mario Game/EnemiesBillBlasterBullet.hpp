#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Physics2D.hpp"
#include "ECS.hpp"

class EnemiesBillBlasterBullet : public Enemy
{
private:
	bool mIsActive{ false };
	Vector2f mPosSrc;
	float mSpeed = 0.05;
	Mario& mMario;

public:
	EnemiesBillBlasterBullet(Mario& mario, Object* parent = nullptr);
	~EnemiesBillBlasterBullet() = default;
	void setActive(
		const Vector2f& posSrc, 
		const bool isRunRight = true
	);
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

