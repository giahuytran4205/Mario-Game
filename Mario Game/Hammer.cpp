#include "Hammer.hpp"

Hammer::Hammer(Object* parent) : Projectile(parent) {
	getComponent<Collision>().setTrigger(true);

	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_anim.loadFromJsonFile("Resources/Animations/Hammer.json");

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	m_physics.setEnableGravity(false);

	m_speed = 0.1f;
	m_isLaunch = false;
}

void Hammer::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		col.m_entity->convertTo<Mario>()->dead();
		destroy();
	}

	if (col.m_entity->isDerivedFrom<Block>()) {
		destroy();
	}
}

void Hammer::hit(bool isDestroy) {

}

void Hammer::update() {
	
}

void Hammer::setDestination(const Vector2f& dest) {
	m_destination = dest;
}

void Hammer::launch() {
	m_isLaunch = true;
	m_anim.play(0);

	Vector2f dist = m_destination - m_transform.getWorldPosition();
	Vector2f vel(m_speed * dist.x / abs(dist.x), 0);
	float t = dist.x / vel.x;
	vel.y = dist.y / t - m_physics.getGravity() * t / 2;

	if (vel.x < 0)
		m_sprite.setScale(1, 1);
	else
		m_sprite.setScale(-1, 1);

	m_physics.setEnableGravity(true);
	m_physics.setBaseVelocity(vel);
}