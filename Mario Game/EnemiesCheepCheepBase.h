#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Mario.hpp"

class EnemiesCheepCheepBase : public Item
{
protected:
	float m_speed = 0.3;
	int mTimeUpdate{ 0 };
	Mario& mMario;

	void dead();

	bool mIsDone{ false };

	bool mIsActive{ false };

public:
	EnemiesCheepCheepBase(Mario& mario, Object* parent);
	~EnemiesCheepCheepBase();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	virtual void update() = 0;
};

