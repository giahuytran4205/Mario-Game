#include "QuestionBlock.hpp"
#include "ItemMushroom.h"
#include "EnemiesSpiny.hpp"

QuestionBlock::QuestionBlock(Environment environment, Object* parent) : Block(parent) {
	m_isHide = false;
	m_renderOrder = 4;
	m_transform.setSize(16, 16);
	m_isEmpty = false;
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

	//RANDOM ITEM
	//int random = std::rand() % 4;

	auto mushroom = new ItemMushroom(ItemMushroom::GREEN, this);
	auto Post = m_transform.getPosition();	
	auto Size = mushroom->getComponent<Transform2D>().getSize().y;
	//mushroom->getComponent<Transform2D>().setPosition(Post.x, Post.y - Size);

	mushroom->getComponent<Transform2D>().setWorldPosition(Post.x ,
		Post.y + Size);

	std::cout << Post.y << "dadas " << Size << "\n";

	mushroom->setActive(Vector2f(m_transform.getPosition().x, m_transform.getPosition().y + Size));


	//auto spiny = new EnemiesSpiny(this->getParent());
	//const bool isRight = true;
	//spiny->getComponent<Transform2D>().setWorldPosition(Post.x + ((isRight ? 1 : -1) * spiny->getTransform2D().getSize().x),
	//	Post.y - spiny->getTransform2D().getSize().y);
	//spiny->setActive(Post, { Post.x + 100, Post.y }, isRight);

}

void QuestionBlock::setHide(bool isHide) {
	m_isHide = isHide;
	m_sprite.setEnable(!isHide);
	getComponent<Collision>().setTrigger(isHide);
}