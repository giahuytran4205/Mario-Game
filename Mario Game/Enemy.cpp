#include "Enemy.hpp"

Enemy::Enemy(Object* parent) : m_anim(addComponent<Animation>(m_sprite)), m_physics(addComponent<Physics2D>()), m_autoControl(addComponent<AutoControl>()) {
	addComponent<Collision>();
	setParent(parent);
	m_physics.setElastic(true);

	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
}

Enemy::~Enemy() {}

void Enemy::die() {
	m_isDead = true;
	destroy();
}