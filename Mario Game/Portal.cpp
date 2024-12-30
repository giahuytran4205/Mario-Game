#include "Portal.hpp"
#include "Mario.hpp"

Portal::Portal() : m_collision(addComponent<Collision>(true)) {
	m_transform.setPosition(0, 0);
	m_destination = { 0, 0 };
	m_inDirection = 0;
	m_outDirection = 0;
	m_destDepth = 0;
	m_isAutoEnter = false;
}

Portal::Portal(const Vector2f& position, const Vector2f& destination, int inDir, int outDir, int destDepth) : Portal() {
	m_transform.setPosition(position);
	m_destination = destination;
	m_inDirection = inDir;
	m_outDirection = outDir;
	m_destDepth = destDepth;
	m_transform.setSize(16, 16);
}

Portal::Portal(const Portal& portal) : Portal() {
	*this = portal;
}

Portal::~Portal() {}

Portal& Portal::operator=(const Portal& portal) {
	m_transform.setPosition(portal.getComponent<Transform2D>().getPosition());
	m_destination = portal.m_destination;
	m_inDirection = portal.m_inDirection;
	m_outDirection = portal.m_outDirection;
	m_destDepth = portal.m_destDepth;
	m_transform.getRect() = portal.m_transform.getRect();
	return *this;
}

void Portal::onCollisionEnter(Collision& col, const Direction& side) {
	/*if (col.m_entity->isType<Mario>()) {
		AutoControl& controller = col.m_entity->getComponent<AutoControl>();
		Physics2D& physics = col.m_entity->getComponent<Physics2D>();

	}*/
}

const Vector2f& Portal::getDestination() {
	return m_destination;
}

Keyboard::Key Portal::getEnterKey() {
	if (m_inDirection == 0)
		return Keyboard::D;

	if (m_inDirection == 1)
		return Keyboard::W;

	if (m_inDirection == 2)
		return Keyboard::A;

	return Keyboard::S;
}

Vector2f Portal::getInDirection() {
	if (m_inDirection == 0)
		return { 1, 0 };

	if (m_inDirection == 1)
		return { 0, -1 };

	if (m_inDirection == 2)
		return { -1, 0 };

	return { 0, 1 };
}

Vector2f Portal::getOutDirection() {
	if (m_outDirection == 0)
		return { 1, 0 };

	if (m_outDirection == 1)
		return { 0, -1 };

	if (m_outDirection == 2)
		return { -1, 0 };

	return { 0, 1 };
}

int Portal::getDestDepth() {
	return m_destDepth;
}

void Portal::setAutoEnter(bool isAutoEnter) {
	m_isAutoEnter = isAutoEnter;
}

bool Portal::isAutoEnter() const {
	return m_isAutoEnter;
}