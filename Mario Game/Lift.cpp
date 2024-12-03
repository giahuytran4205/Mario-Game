#include "Lift.hpp"
#include <iostream>

Lift::Lift(Object* parent) : m_physics(addComponent<Physics2D>()), m_sprite(this) {
	addComponent<Collision>();
	setParent(parent);
	
	m_direction = { 0, 0 };
	m_speed = 0;
	m_startOffset = 0;
	m_endOffset = 0;
	m_phase = 0;
	m_isLaunch = false;

	m_sprite.setTexture(TextureManager::getTile("Resources/Animations/Items&Objects.png", IntRect(208, 128, 8, 8), true));
	m_sprite.setTextureRect(IntRect(0, 0, 48, 8));
	
	m_transform.setSize(48, 8);
}

Lift::Lift(const Vector2f& pos, Object* parent) : Lift(parent) {
	m_transform.setPosition(pos);
}

Lift::Lift(const Vector2f& pos, float length, float startOffset, float endOffset, const Vector2f& direction, float speed, bool isLaunch, Object* parent) : Lift(pos, parent) {	
	m_startOffset = startOffset;
	m_endOffset = endOffset;
	m_direction = direction;
	m_speed = speed;
	m_phase = acos(1 - 2 * (pos.y - startOffset) / (endOffset - startOffset));
	
	m_isLaunch = isLaunch;
	
	m_sprite.setTextureRect(IntRect(0, 0, length, 8));
	
	m_transform.setPosition(pos);
	m_transform.setSize(length, 8);
}

Lift::~Lift() {}

void Lift::update() {
	if (m_isLaunch) {
		m_phase += deltaTime.asMilliseconds() / 1000.0;
		if (m_phase > 2 * PI)
			m_phase -= 2 * PI;

		float x = m_transform.getPosition().x * abs(m_direction.x);
		float y = m_transform.getPosition().y * abs(m_direction.y);

		float minX = m_startOffset * abs(m_direction.x);
		float maxX = m_endOffset * abs(m_direction.x);
		float minY = m_startOffset * abs(m_direction.y);
		float maxY = m_endOffset * abs(m_direction.y);

		m_physics.setBaseVelocityY(0.5 * 0.001 * (m_endOffset - m_startOffset) * sin(m_phase));

		cout << m_transform.getPosition().y << '\n';
	}

	if (m_mario && m_mario->isOnGround()) {
		m_mario->getComponent<Physics2D>().setBaseVelocityY(m_physics.getBaseVelocity().y);
	}
	m_mario = nullptr;
}

void Lift::onCollisionEnter(Collision& col) {
	int side = m_transform.getRect().tangentSide(col.getCollider());

	if (side == 1 && col.m_entity->isType<Mario>()) {
		m_mario = col.m_entity->convertTo<Mario>();
	}
}

void Lift::setDirection(const Vector2f& direction) {
	m_direction = direction;
}

void Lift::setMovementRange(float startOffset, float endOffset) {
	m_startOffset = startOffset;
	m_endOffset = endOffset;
}

void Lift::setSpeed(float speed) {
	m_speed = speed;
}

void Lift::launch() {
	m_isLaunch = true;
}

void Lift::stop() {
	m_isLaunch = false;

	m_physics.setBaseVelocity({ 0, 0 });
	m_physics.setVelocity({ 0, 0 });
}