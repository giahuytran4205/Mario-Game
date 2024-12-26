#include "Enemy.hpp"

Enemy::Enemy(Object* parent, const bool isNeedCollision) : m_anim(addComponent<Animation>(m_sprite)),
m_physics(addComponent<Physics2D>()), 
m_autoControl(addComponent<AutoControl>())
, m_sound(addComponent<SoundComponent>()) {
	if (isNeedCollision) {
		addComponent<Collision>();
	}
	setParent(parent);
	m_physics.setElastic(true);
}

Enemy::~Enemy() {}