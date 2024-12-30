#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Projectile.hpp"

class Hammer : public Projectile
{
private:
	Vector2f m_destination;
	bool m_isLaunch;

public:
	Hammer(Object* parent = nullptr);
	~Hammer() = default;

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
	void setDestination(const Vector2f& dest);
	void launch();
};

