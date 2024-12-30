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
#include "SoundComponent.hpp"
class EnemiesGoomba : public Enemy
{
private:
	enum State {
		WALK,
		DIE
	};

public:
	EnemiesGoomba(Object* parent = nullptr);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void die();
	void update();
};

