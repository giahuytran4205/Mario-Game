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

	
	bool m_onWall{ false };
	float m_speed = -0.05f;
	int m_dir = 1;
	
	bool m_isDead;

	float m_invincibleTimer = 0.0f; // tạo hàm này để khi mario bị biến xuống dạng nhỏ hơn thì bất tử tạm thời 
public:
	EnemiesGoomba(Object* parent = nullptr);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

