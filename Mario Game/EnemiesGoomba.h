#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "GameManager.hpp"
class EnemiesGoomba : public Item
{
	float m_speed_Vy = 0.0f;
	const float G = 0.001f;
	bool m_onWall{ false };
	float m_speed = 0.2;
public:
	EnemiesGoomba(Object* parent = nullptr);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

