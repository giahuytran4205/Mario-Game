#pragma once

#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"

class EnemiesKoopaTroopa : public Item
{
public:
	enum State {
		NORMAL,
		STEP_2,
		STEP_3
	};
private:
	float m_speed = 0.1;
	bool mIsStep2{ false };
	bool mIsStep3{ false };
	bool m_onWall{ false };
	int mTimeUpdate{ 0 };
	State mState{ NORMAL };
	//Physics2D& m_physics2D;
public:
	EnemiesKoopaTroopa( Object* parent = nullptr);
	~EnemiesKoopaTroopa();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
	State getState();

};

