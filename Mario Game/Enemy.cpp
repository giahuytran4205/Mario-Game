#include "Enemy.hpp"

Enemy::Enemy(Object* parent, const bool isNeedCollision) : m_anim(addComponent<Animation>(m_sprite)),
m_physics(addComponent<Physics2D>()), 
m_autoControl(addComponent<AutoControl>())
, m_sound(addComponent<SoundComponent>()),
m_collision(addComponent<Collision>())
{
	if (!isNeedCollision) {
		m_collision.setSkipResolveCollide(true);
	}
	setParent(parent);
	m_physics.setElastic(true);
	m_sprite.setRenderOrder(3);
}

Enemy::~Enemy() {}