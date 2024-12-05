#include "SingleBalanceLift.hpp"

SingleBalanceLift::SingleBalanceLift(Object* parent) : Lift(parent) {
	m_otherLift = nullptr;
	m_phase = 0;
	m_isLaunch = false;
	m_amplitude = 0;
}

SingleBalanceLift::SingleBalanceLift(const Vector2f& pos, float amplitude, float speed) : SingleBalanceLift() {
	m_amplitude = amplitude;
	m_speed = speed;
	m_transform.setPosition(pos);
}

SingleBalanceLift::~SingleBalanceLift() {}

void SingleBalanceLift::update() {
	m_otherLift->setParent(m_parent);

	if (m_mario && m_isLaunch) {
		m_phase = acos(1 - ((m_transform.getWorldPosition().y - m_otherLift->getComponent<Transform2D>().getWorldPosition().y) / 2 + m_amplitude) / m_amplitude);

		m_phase += deltaTime.asMilliseconds() * m_speed;

		if (m_phase > PI)
			m_phase = PI;

		float vel = m_speed * m_amplitude * sin(m_phase);

		m_physics.setBaseVelocityY(vel);
		m_otherLift->getComponent<Physics2D>().setBaseVelocityY(-vel);

		if (m_mario->isOnGround())
			m_mario->getComponent<Physics2D>().addVelocity({ 0, m_physics.getBaseVelocity().y });

	}
	if (!m_mario && m_isLaunch) {
		m_physics.setBaseVelocityY(0);
		m_otherLift->getComponent<Physics2D>().setBaseVelocityY(0);
	}

	m_mario = nullptr;
}

void SingleBalanceLift::onCollisionEnter(Collision& col) {
	int side = m_transform.getRect().tangentSide(col.getCollider());

	if (side == 1 && col.m_entity->isType<Mario>()) {
		m_mario = col.m_entity->convertTo<Mario>();
		m_isLaunch = true;
		m_otherLift->m_isLaunch = false;
	}
}

void SingleBalanceLift::setAmplitude(float amplitude) {
	m_amplitude = amplitude;
}

void SingleBalanceLift::linkOtherLift(SingleBalanceLift* other) {
	m_otherLift = other;
	m_balancePos = (m_transform.getWorldPosition() + m_otherLift->getComponent<Transform2D>().getWorldPosition()) / 2.0f;
}