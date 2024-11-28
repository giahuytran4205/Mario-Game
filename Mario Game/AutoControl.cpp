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

		int elapsedTime = m_currentControl.duration - m_countdown;
		
		if (m_currentControl.action)
			m_currentControl.action(elapsedTime);
	}
	else if (!m_controlQueue.empty()) {
		ControlInfo info = m_controlQueue.front();
		m_controlQueue.pop();

		m_currentControl = info;

		m_physics->setVelocity({ 0, 0 });

		if (info.duration == 0) {
			m_transform->setPosition(info.pos);
		}
		else {
			m_countdown = info.duration;

			Vector2f dist = info.pos - m_transform->getPosition();
			Vector2f vel = dist / (float)info.duration - info.acceleration * (float)info.duration / 2.0f;

			m_physics->setBaseVelocity(vel);
			m_physics->setAcceleration(info.acceleration);
		}
	}
	else {
		if (m_isControlled) {
			m_isControlled = false;
			m_physics->setAcceleration({ 0, 0 });
		}
	}
}

void AutoControl::addMoveByPoint(const Vector2f& dest, int duration, const Vector2f& acceleration, function<void(int)> action) {
	m_isControlled = true;
	m_controlQueue.push({ dest, duration, acceleration, action });
}

void AutoControl::addMoveByDistance(const Vector2f& distance, int duration, const Vector2f& acceleration, function<void(int)> action) {
	m_isControlled = true;
	ControlInfo last = m_controlQueue.back();
	m_controlQueue.push({ last.pos + distance, duration, acceleration, action });
}

void AutoControl::addWaitForMiliseconds(int duration, function<void(int)> action) {
	m_isControlled = true;
	ControlInfo last = m_controlQueue.back();
	m_controlQueue.push({ last.pos, duration, { 0, 0 }, action });
}

bool AutoControl::isControlled() {
	return m_isControlled;
}