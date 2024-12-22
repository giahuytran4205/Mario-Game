#include "Character.hpp"
#include "Object.hpp"

Character::Character() {
	m_direction = Direction::RIGHT;
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

void Character::setTexture(Texture& texture) {
	m_sprite.setTexture(texture);
}

bool Character::isOnGround() {
	return m_onGround;
}

bool Character::isOnWall() {
	return m_onWall;
}

//virtual void Character::onCollisionEnter(Collision& col) {}

/*void Character::render(RenderWindow &window) {
	window.draw(m_sprite);
}*/