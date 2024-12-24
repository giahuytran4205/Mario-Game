#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "AutoControl.hpp"

class EnemiesGoomba : public Enemy
{
private:
	enum State {
		WALK,
		DIE
	};

	AutoControl& m_autoControl;
	float m_speed_Vy = 0.0f;
	const float G = 0.001f;
	bool m_onWall{ false };
	float m_speed = 0.1;
	int m_dir = 1;

public:
	EnemiesGoomba(Object* parent = nullptr);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

