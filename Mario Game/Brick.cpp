#include "Brick.hpp"

Brick::Brick(Object* parent) : Block(parent) {
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 0, 16, 16)));
}

Brick::~Brick() {}

void Brick::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>()) {
		int side = m_transform.tangentSide(col.getCollider());

		if (side == 3) {
			hit();
		}
	}
}

void Brick::hit() {

}