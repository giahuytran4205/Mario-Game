#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"

class Brick : public Block {
private:

public:
	Brick(Environment environment = OVERWORLD, Object* parent = nullptr);
	~Brick();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
};