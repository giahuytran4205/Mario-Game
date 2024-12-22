#include "Lift.hpp"
#include <iostream>

Lift::Lift(Object* parent) : m_physics(addComponent<Physics2D>()), m_sprite(this) {
	addComponent<Collision>();
	setParent(parent);
	
	m_transform.setAnchor(0.5, 0);
	m_sprite.setAnchor(0.5, 0);

	m_transform.setSize(48, 8);

	m_direction = DOWN;
	m_speed = 0;
	m_startOffset = 0;
	m_endOffset = 0;
	m_phase = 0;
	m_isCircular = false;
	m_isLaunch = false;

	m_sprite.setTexture(TextureManager::getTile("Resources/Animations/Items&Objects.png", IntRect(208, 128, 8, 8), true));
	m_sprite.setTextureRect(IntRect(0, 0, 48, 8));
}

Lift::Lift(const Vector2f& pos, Object* parent) : Lift(parent) {
	m_transform.setPosition(pos);
}

Lift::Lift(const Vector2f& pos, float startOffset, float endOffset, Direction direction, bool isLaunch, float length, float speed, Object* parent) : Lift(pos, parent) {
	m_startOffset = startOffset;
	m_endOffset = endOffset;
	m_direction = direction;
	m_speed = speed;

	if (m_direction == LEFT || m_direction == RIGHT)
		m_phase = acos(1 - 2 * (pos.x - startOffset) / (endOffset - startOffset));
	if (m_direction == UP || m_direction == DOWN)
		m_phase = acos(1 - 2 * (pos.y - startOffset) / (endOffset - startOffset));

	m_isLaunch = isLaunch;
	
	m_sprite.setTextureRect(IntRect(0, 0, length, 8));
	
	m_transform.setPosition(pos);
	m_transform.setSize(length, 8);
}

Lift::~Lift() {}

void Lift::update() {
	if (m_isLaunch) {
		m_phase += deltaTime.asMilliseconds() * m_speed;

		if (m_isCircular && m_phase > PI) {
			m_phase -= PI;

			if (m_direction == LEFT || m_direction == RIGHT)
				m_transform.setWorldPosition(m_startOffset, m_transform.getWorldPosition().y);
			if (m_direction == UP || m_direction == DOWN)
				m_transform.setWorldPosition(m_transform.getWorldPosition().x, m_startOffset);
		}

		if (m_phase > 2 * PI) {
			m_phase -= 2 * PI;
		}

		float vel = 0.5f * m_speed * (m_endOffset - m_startOffset) * sin(m_phase);

		if (m_direction == RIGHT)
			m_physics.setBaseVelocityX(vel);
		if (m_direction == LEFT)
			m_physics.setBaseVelocityX(-vel);
		if (m_direction == DOWN)
			m_physics.setBaseVelocityY(vel);
		if (m_direction == UP)
			m_physics.setBaseVelocityY(-vel);
	}

	if (m_mario && m_mario->isOnGround()) {
		if (m_direction == LEFT || m_direction == RIGHT)
			m_mario->getComponent<Physics2D>().addVelocity({ m_physics.getBaseVelocity().x, 0 });
		if (m_direction == UP || m_direction == DOWN)
			m_mario->getComponent<Physics2D>().addVelocity({ 0, m_physics.getBaseVelocity().y });
	}
	m_mario = nullptr;
}

void Lift::onCollisionEnter(Collision& col, const Direction& side) {
	if (side == Direction::UP && col.m_entity->isType<Mario>()) {
		m_mario = col.m_entity->convertTo<Mario>();
	}
}

void Lift::setDirection(Direction direction) {
	m_direction = direction;
}

void Lift::setMovementRange(float startOffset, float endOffset) {
	m_startOffset = startOffset;
	m_endOffset = endOffset;
}

void Lift::setSpeed(float speed) {
	m_speed = speed;
}

void Lift::setCircular(bool isCircular) {
	m_isCircular = true;
}

void Lift::launch() {
	m_isLaunch = true;
}

void Lift::stop() {
	m_isLaunch = false;

	m_physics.setBaseVelocity({ 0, 0 });
	m_physics.setVelocity({ 0, 0 });
}