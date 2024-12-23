#include "Enemy.hpp"

Enemy::Enemy(Object* parent) : m_anim(addComponent<Animation>(m_sprite)), m_physics(addComponent<Physics2D>()) {
	addComponent<Collision>();
	setParent(parent);
	m_physics.setElastic(true);
}

Enemy::~Enemy() {}