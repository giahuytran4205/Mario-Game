#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "Projectile.hpp"

class BulletBill : public Projectile {
public:
	BulletBill(Object* parent = nullptr);
	BulletBill(const Vector2f& direction, Object* parent = nullptr);
	~BulletBill() = default;
	
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

