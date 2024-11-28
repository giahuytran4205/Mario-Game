#include "AutoControl.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"

AutoControl::AutoControl() {
	m_physics = nullptr;
	m_transform = nullptr;
	m_isControlled = false;
	m_countdown = 0;
}

AutoControl::~AutoControl() {}

void AutoControl::init() {
	m_physics = &m_entity->getComponent<Physics2D>();
	m_transform = &m_entity->getComponent<Transform2D>();
}

void AutoControl::update() {
	m_physics->setEnableGravity(!m_isControlled);

	if (m_countdown > 0) {
		m_countdown -= deltaTime.asMilliseconds();
	}
	else if (!m_controlQueue.empty()) {
		ControlInfo info = m_controlQueue.front();
		m_controlQueue.pop();

		m_physics->setVelocity({ 0, 0 });

		if (info.duration == 0) {
			m_transform->setPosition(info.pos);
		}
		else {
			m_countdown = info.duration;
			m_countdown -= deltaTime.asMilliseconds();

			Vector2f dist = info.pos - m_transform->getPosition();
			Vector2f vel = dist / (float)info.duration + info.acceleration * (float)info.duration / 2.0f;

			m_physics->setBaseVelocity(vel);
			m_physics->setAcceleration(info.acceleration);
		}
	}
	else {
		m_isControlled = false;
	}
}

void AutoControl::addControl(const Vector2f& dest, int duration, const Vector2f& acceleration) {
	m_isControlled = true;
	m_controlQueue.push({ dest, duration, acceleration });
}

bool AutoControl::isControlled() {
	return m_isControlled;
}