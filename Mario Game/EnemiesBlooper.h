#pragma once

#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Mario.hpp"

class EnemiesBlooper : public Item
{
private:
	float m_speed = 0.1;
	int mTimeUpdate{ 0 };
	Mario& mMario;
public:
	EnemiesBlooper(Mario& mario, Object* parent);
	~EnemiesBlooper();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();

};

