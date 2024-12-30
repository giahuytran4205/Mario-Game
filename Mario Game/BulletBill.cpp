#include "BulletBill.hpp"
#include "GameManager.hpp"

BulletBill::BulletBill(Object* parent) : Projectile(parent) {
	getComponent<Collision>().setTrigger(true);

	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Enemies.png", IntRect(560, 16, 16, 16)));
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	m_physics.setEnableGravity(false);

	m_speed = 0.2f;
	m_age = 5000;
}

BulletBill::BulletBill(const Vector2f& direction, Object* parent) : BulletBill(parent) {
	setDirection(direction);
	m_physics.setBaseVelocity(direction * m_speed);
}

void BulletBill::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		if (side == Direction::UP) {
			//m_sound.play(SoundTrack::STOMP);
			destroy();
			col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setVelocityY(0);
			col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
		}
		else {
			col.m_entity->convertTo<Mario>()->dead();
		}
	}

	if (col.m_entity->isType<Fireball>()) {
		destroy();
	}
}

void BulletBill::update() {
	m_age -= deltaTime.asMilliseconds();
	if (m_age <= 0)
		destroy();

	if (m_direction.x < 0)
		m_sprite.setScale(1, 1);
	else
		m_sprite.setScale(-1, 1);
}
