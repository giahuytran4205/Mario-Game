#pragma once
#include "Block.hpp"
#include "TextureManager.hpp"

class EmptyBlock : public Block {
private:

public:
	EmptyBlock(Object* parent = nullptr);
	~EmptyBlock();
};