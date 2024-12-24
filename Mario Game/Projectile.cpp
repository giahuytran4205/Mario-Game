#include "Projectile.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"

Projectile::Projectile(Object* parent) : m_physics(addComponent<Physics2D>()), m_anim(addComponent<Animation>(m_sprite)) {
	m_physics.setElastic(true);
	addComponent<Collision>();
	setParent(parent);
	m_sprite.setParent(this);

	m_damage = 0;
	m_maxDistance = 0;
	m_age = 0;
	m_speed = 0;
}

Projectile::~Projectile() {

}

int Projectile::getDamage() const {
	return m_damage;
}

Vector2f Projectile::getDirection() const {
	return m_direction;
}

void Projectile::setDamage(int damage) {
	m_damage = damage;
}

float Projectile::getMaxDistance() const {
	return m_maxDistance;
}

void Projectile::setMaxDistance(float maxDistance) {
	m_maxDistance = maxDistance;
}

void Projectile::setDirection(const Vector2f& direction) {
	m_direction = normalize(direction);
	m_physics.setBaseVelocity(m_direction * m_speed);
}

int Projectile::getAge() const {
	return m_age;
}

void Projectile::update() {
	m_age++;
}