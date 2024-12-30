#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "Projectile.hpp"
#include "SoundComponent.hpp"

class Fireball : public Projectile {
public:
	Fireball(Object* parent = nullptr, const Vector2f& direction = {0, 0});
	~Fireball();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
};