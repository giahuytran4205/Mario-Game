#include "QuestionBlock.hpp"
#include "ItemFactory.hpp"
#include "Beanstalk.hpp"

QuestionBlock::QuestionBlock(Environment environment, Object* parent) : Block(parent) {
	m_isHide = false;
	m_renderOrder = 4;
	m_transform.setSize(16, 16);
	m_isEmpty = false;
	m_containBeanstalk = false;
	m_environment = environment;

	if (environment == Environment::OVERWORLD)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 0, 16, 16)));
	if (environment == Environment::UNDERGROUND)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 32, 16, 16)));
	if (environment == Environment::ATHLETIC)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 0, 16, 16)));
	if (environment == Environment::CASTLE)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 64, 16, 16)));
	if (environment == Environment::UNDERWATER)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(384, 96, 16, 16)));
}

QuestionBlock::~QuestionBlock() {

}

void QuestionBlock::onCollisionEnter(Collision& col, const Direction& side) {
	if (!m_isEmpty && col.m_entity->isType<Mario>()) {
		if (side == Direction::DOWN) {
			if (m_isHide) {
				Mario* mario = col.m_entity->convertTo<Mario>();
				Transform2D& marioTF = mario->getComponent<Transform2D>();

				mario->getComponent<Physics2D>().setBaseVelocityY(0.01);
				mario->getComponent<Physics2D>().setVelocityY(0);
				marioTF.setWorldPosition(marioTF.getWorldPosition().x, m_transform.bottom + marioTF.height / 2);
			}

			hit();
		}
	}
}

void QuestionBlock::hit() {
	m_physics2D.bounce(-0.06);
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(48, 0, 16, 16)));
	m_isEmpty = true;
	setHide(false);

	if (m_containBeanstalk) {
				
	}
	else {
		Item* item = ItemFactory::getInstance()->getItem();
		if (item) {
			item->getComponent<Transform2D>().setWorldPosition(m_transform.getWorldCenter());
			item->appear();
		}
	}
}

void QuestionBlock::setHide(bool isHide) {
	m_isHide = isHide;
	m_sprite.setEnable(!isHide);
	getComponent<Collision>().setTrigger(isHide);
}

void QuestionBlock::addBeanstalk() {
	m_containBeanstalk = true;
}