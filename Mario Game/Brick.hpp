#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"

class Brick : public Block {
private:

public:
	Brick(Object* parent = nullptr);
	~Brick();

	void onCollisionEnter(Collision& col);
	void hit();
};