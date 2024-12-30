#pragma once

#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Enemy.hpp"

class EnemiesKoopaTroopa : public Enemy
{
public:
	EnemiesKoopaTroopa(Object* parent = nullptr);
	~EnemiesKoopaTroopa();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update();
	void die();
};

