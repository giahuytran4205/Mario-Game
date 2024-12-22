#include "Collision.hpp"
#include "Enum.hpp"

Collision::Collision(bool isTrigger) {
	m_transform = nullptr;
	m_isTrigger = isTrigger;
	m_isUseOwnCollider = false;
	m_localCol = FRect(0, 0, 0, 0);
}

Collision::Collision(const FRect& collider, bool isTrigger) : Collision(isTrigger) {
	m_localCol = collider;
	m_isUseOwnCollider = true;
}

Collision::~Collision() {}

void Collision::init() {
	m_transform = &m_entity->getComponent<Transform2D>();
	m_collider = m_transform;
	CollisionManager::addCollider(this);
}

void Collision::resolveCollide(Collision& col, Direction& side, bool isTrigger) {
	FRect collider = col.getCollider();
	Transform2D& bodyTF = m_entity->getComponent<Transform2D>();

	FRect rect = collider;
	rect = {rect.left - m_collider->width / 2, rect.top - m_collider->height / 2, rect.width + m_collider->width, rect.height + m_collider->height};

	Vector2f colVel, bodyVel;
	if (col.m_entity->hasComponent<Physics2D>()) {
		colVel = col.m_entity->getComponent<Physics2D>().getVelocity() + col.m_entity->getComponent<Physics2D>().getBaseVelocity();
	}

	if (m_entity->hasComponent<Physics2D>()) {
		bodyVel = m_entity->getComponent<Physics2D>().getVelocity() + m_entity->getComponent<Physics2D>().getBaseVelocity();
	}

	if (!isTrigger && col.m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = col.m_entity->getComponent<Physics2D>();
		physics.setBaseVelocity({ 0, 0 });
		physics.setVelocity({ 0, 0 });
	}

	if (!isTrigger && m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = m_entity->getComponent<Physics2D>();
		physics.setBaseVelocity({ 0, 0 });
		physics.setVelocity({ 0, 0 });
	}


	if (rect.contains(bodyTF.getLastCenter()) && rect.contains(bodyTF.getWorldCenter())) {
		if (abs(colVel.x) > abs(colVel.y)) {
			if (colVel.x <= 0) {
				if (!isTrigger)
					bodyTF.setCenter(collider.left - m_collider->width / 2, bodyTF.getWorldPosition().y);
				
				side = Direction::RIGHT;
			}
			else {
				if (!isTrigger)
					bodyTF.setCenter(collider.right + m_collider->width / 2, bodyTF.getWorldPosition().y);
				
				side = Direction::LEFT;
			}

			if (!isTrigger)
				m_entity->getComponent<Physics2D>().setBaseVelocityY(0.1f);
		}
		else {
			if (colVel.y <= 0) {
				if (!isTrigger)
					bodyTF.setCenter(bodyTF.getWorldPosition().x, collider.top - m_collider->height / 2);
				
				side = Direction::DOWN;
			}
			else {
				if (!isTrigger)
					bodyTF.setCenter(bodyTF.getWorldPosition().x, collider.bottom + m_collider->height / 2);
				
				side = Direction::UP;

				if (!isTrigger && m_entity->hasComponent<Physics2D>()) {
					Physics2D& physics = m_entity->getComponent<Physics2D>();
					physics.setBaseVelocityY(colVel.y + 0.05);
				}

			}
		}
		return;
	}

	Vector2f tangentPoint = getTangentPoint(col, side);
	Vector2f vel = bodyTF.getWorldCenter() - tangentPoint;
	if (side == Direction::LEFT || side == Direction::RIGHT)
		vel.x = 0;
	else vel.y = 0;

	if (!isTrigger && m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = m_entity->getComponent<Physics2D>();

		if (side == Direction::UP)
			physics.setBaseVelocityY(colVel.y + 0.05);
		if (side == Direction::LEFT || side == Direction::RIGHT)
			physics.setBaseVelocityY(0.1f);
	}

	if (!isTrigger)
		bodyTF.setCenter(tangentPoint + vel);
}

void Collision::update() {

}

void Collision::lateUpdate() {
	
}

FRect Collision::getCollider() const {
	if (m_isUseOwnCollider)
		return FRect(m_transform->left + m_localCol.left, m_transform->top + m_localCol.top, m_localCol.width, m_localCol.height);

	return *m_transform;
}

void Collision::onCollisionEnter(Collision& col, const Direction& side) {
	m_entity->onCollisionEnter(col, side);
	col.m_entity->onCollisionEnter(*this, getOpposite(side));
}

void Collision::setTrigger(bool isTrigger) {
	m_isTrigger = isTrigger;
}

bool Collision::isTrigger() {
	return m_isTrigger;
}

Vector2f Collision::getTangentPoint(const Collision& col, Direction& side) const {
	Line line(m_entity->getComponent<Transform2D>().getLastCenter(), m_entity->getComponent<Transform2D>().getWorldCenter());

	FRect rect = col.getCollider();
	FRect bodyRect = m_entity->getComponent<Transform2D>();

	rect = { rect.left - bodyRect.width / 2, rect.top - bodyRect.height / 2, rect.width + bodyRect.width, rect.height + bodyRect.height };
	Vector2f res = line.raycast(rect, side);
	side = getOpposite(side);
	return res;
}