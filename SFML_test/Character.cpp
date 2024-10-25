#include "Character.hpp"

Character::Character() {

}

Character::~Character() {

}

int Character::getMaxHealth() {
	return m_maxHealth;
}

void Character::setMaxHealth(int maxHealth) {
	m_maxHealth = maxHealth;
}

int Character::getHealth() {
	return m_health;
}

void Character::setHealth(int health) {
	m_health = health;
}

void Character::setTexture(const Texture& texture) {
	m_sprite.setTexture(texture);
}

bool Character::isOnGround() {
	return m_onGround;
}

//virtual void Character::onCollisionEnter(Collision& col) {}

/*void Character::render(RenderWindow &window) {
	window.draw(m_sprite);
}*/