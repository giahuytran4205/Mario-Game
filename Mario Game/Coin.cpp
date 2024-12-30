#include "Coin.hpp"

Coin::Coin(Object* parent) : Item(parent) {
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
	m_anim.play(0);

	m_physics.setEnable(false);
}

Coin::Coin(float x, float y, Object* parent) : Coin(parent) {
	m_transform.setPosition(x, y);
}

Coin::Coin(const Vector2f& pos, Object* parent) : Coin(pos.x, pos.y, parent) {

}

Coin::~Coin() {}

void Coin::update() {

}

void Coin::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		col.m_entity->convertTo<Mario>()->earnCoins(1);
		col.m_entity->convertTo<Mario>()->addScore(100);
		SceneManager::getInstance()->getCurrentScene().getComponent<SoundComponent>().play(SoundTrack::COIN);
		destroy();
	}
}