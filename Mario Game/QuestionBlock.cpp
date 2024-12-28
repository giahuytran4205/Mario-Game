#include "QuestionBlock.hpp"
#include "ItemMushroom.h"
#include "EnemiesSpiny.h"
#include "ItemFireFlower.hpp"
#include "ItemStar.hpp"


QuestionBlock::QuestionBlock(Environment environment, Object* parent, const RandomQuestion::Type type) :
	Block(parent), mType(type) {
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

	m_sprite.setRenderOrder(3);
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

	//auto mushroom = new ItemMushroom(ItemMushroom::GREEN, this->getParent());
	//auto Post = m_transform.getPosition();	
	//auto Size = mushroom->getComponent<Transform2D>().getSize().y;
	//mushroom->getComponent<Transform2D>().setWorldPosition(Post.x - mushroom->getTransform2D().getSize().x/2,
	//	Post.y - Size);
	//mushroom->setActive(Vector2f(m_transform.getPosition().x - mushroom->getTransform2D().getSize().x / 2, Post.y - 1.5*Size));


	//{
	//	auto fireFlower = new ItemFireFlower(this->getParent());
	//	auto Post = m_transform.getPosition();
	//	auto Size = fireFlower->getComponent<Transform2D>().getSize().y;
	//	fireFlower->getComponent<Transform2D>().setWorldPosition(Post.x - fireFlower->getTransform2D().getSize().x / 2,
	//		Post.y - Size);
	//	fireFlower->setActive(Vector2f(m_transform.getPosition().x - fireFlower->getTransform2D().getSize().x / 2, Post.y - 1.5 * Size));

	//}

	//{
	//	auto star = new ItemStar(this->getParent());
	//	auto Post = m_transform.getPosition();
	//	auto Size = star->getComponent<Transform2D>().getSize().y;
	//	star->getComponent<Transform2D>().setWorldPosition(Post.x - star->getTransform2D().getSize().x / 2,
	//		Post.y - Size);
	//	star->setActive(Vector2f(m_transform.getPosition().x - star->getTransform2D().getSize().x / 2, Post.y - 1.5 * Size));

	//}

	// check type
	int type = 0;
	
	if (mType != RandomQuestion::UNKNOW) {
		type = mType;
	}
	else if(mRadom == nullptr){
		type = RandomQuestion::COIN;
	}
	else {
		type = mRadom->getRadomType();
	}
	switch (type)
	{
	case RandomQuestion::COIN: {
		// TODO
		break;
	}
	case RandomQuestion::MUSH_ROOM: {
		auto mushroom = new ItemMushroom(ItemMushroom::GREEN, this->getParent());
		auto Post = m_transform.getPosition();	
		auto Size = mushroom->getComponent<Transform2D>().getSize().y;
		mushroom->getComponent<Transform2D>().setWorldPosition(Post.x - mushroom->getTransform2D().getSize().x/2,
			Post.y - Size);
		mushroom->setActive(Vector2f(m_transform.getPosition().x - mushroom->getTransform2D().getSize().x / 2, Post.y - 1.5*Size));

		break;
	}
	case RandomQuestion::FLOWER: {
		auto fireFlower = new ItemFireFlower(this->getParent());
		auto Post = m_transform.getPosition();
		auto Size = fireFlower->getComponent<Transform2D>().getSize().y;
			fireFlower->getComponent<Transform2D>().setWorldPosition(Post.x - fireFlower->getTransform2D().getSize().x / 2,
			Post.y - Size);
		fireFlower->setActive(Vector2f(m_transform.getPosition().x - fireFlower->getTransform2D().getSize().x / 2, Post.y - 1.5 * Size));

		break;
	}
	case RandomQuestion::STAR: {
		auto star = new ItemStar(this->getParent());
		auto Post = m_transform.getPosition();
		auto Size = star->getComponent<Transform2D>().getSize().y;
		star->getComponent<Transform2D>().setWorldPosition(Post.x - star->getTransform2D().getSize().x / 2,
			Post.y - Size);
		star->setActive(Vector2f(m_transform.getPosition().x - star->getTransform2D().getSize().x / 2, Post.y - 1.5 * Size));
		break;
	}
	default:
		break;
	}

}

void QuestionBlock::setHide(bool isHide) {
	m_isHide = isHide;
	m_sprite.setEnable(!isHide);
	getComponent<Collision>().setTrigger(isHide);
}

void QuestionBlock::setRandom(std::shared_ptr<RandomQuestion> radom)
{
	mRadom = radom;
	if (mRadom != nullptr) {
		mType = RandomQuestion::UNKNOW;
	}
}

void QuestionBlock::setFixType(RandomQuestion::Type type)
{
	mType = type;
}
