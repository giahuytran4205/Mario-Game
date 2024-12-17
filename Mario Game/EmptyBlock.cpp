#include "EmptyBlock.hpp"
#include <iostream>

EmptyBlock::EmptyBlock(Object* parent) : Block(parent) {
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(48, 0, 16, 16)));
	m_sprite.setRenderOrder(5);
	m_sprite.getComponent<Transform2D>().setPosition(0, 0);
	m_transform.setSize(16, 16);
	cout << m_transform.getWorldPosition().x << " " << m_transform.getWorldPosition().y << '\n';
}

EmptyBlock::~EmptyBlock() {}

void EmptyBlock::onCollisionEnter(Collision& col, const Direction& side) {
	
}