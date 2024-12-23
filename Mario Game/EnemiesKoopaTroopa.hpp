#pragma once

#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "GameManager.hpp"
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
	float m_speed_Vy = 0.0f;
	const float G = 0.0708f;
public:
	EnemiesKoopaTroopa( Object* parent = nullptr);
	~EnemiesKoopaTroopa();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
	State getState();

};

