#pragma once
#include "Block.hpp"
#include "TextureManager.hpp"
#include "Collision.hpp"

class EmptyBlock : public Block {
private:

public:
	EmptyBlock(Object* parent = nullptr);
	~EmptyBlock();

	void onCollisionEnter(Collision& col, const Direction& side) override;
};