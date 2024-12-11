#include "EmptyBlock.hpp"

EmptyBlock::EmptyBlock(Object* parent) : Block(parent) {
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(48, 0, 16, 16)));
}

EmptyBlock::~EmptyBlock() {}