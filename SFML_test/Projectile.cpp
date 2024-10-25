#include "Projectile.hpp"

Projectile::Projectile(int damage, int maxDistance) {
	m_damage = damage;
	m_maxDistance = maxDistance;
	m_age = 0;
}

Projectile::~Projectile() {

}

int Projectile::getDamage() {
	return m_damage;
}

void Projectile::setDamage(int damage) {
	m_damage = damage;
}

float Projectile::getMaxDistance() {
	return m_maxDistance;
}

void Projectile::setMaxDistance(float maxDistance) {
	m_maxDistance = maxDistance;
}

int Projectile::getAge() {
	return m_age;
}

void Projectile::Update() {
	m_age++;
}