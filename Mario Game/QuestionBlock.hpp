#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "EmptyBlock.hpp"
#include "TextureManager.hpp"

class QuestionBlock : public Block {
private:

public:
	QuestionBlock(Object* parent = nullptr);
	~QuestionBlock();

	void onCollisionEnter(Collision& col) override;
	void hit();
};