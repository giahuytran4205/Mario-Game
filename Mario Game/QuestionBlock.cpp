#include "QuestionBlock.hpp"

QuestionBlock::QuestionBlock(Object* parent) : Block(parent) {
	addComponent<Collision>();
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 0, 16, 16)));
	m_renderOrder = 4;
	m_transform.setSize(16, 16);
}

QuestionBlock::~QuestionBlock() {

}

void QuestionBlock::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>()) {
		int side = m_transform.tangentSide(col.getCollider());

		if (side == 3) {
			hit();
		}
	}
}

void QuestionBlock::hit() {
	m_physics2D.bounce(-0.06);
	Block::operator=(EmptyBlock(m_parent));
}