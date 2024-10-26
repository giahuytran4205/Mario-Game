#include "Collision.hpp"
#include "Transform2D.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
using namespace sf;

vector<Collision*> Collision::m_colliders;

void Collision::init() {
	if (!m_entity->hasComponent<Transform2D>()) {
		m_entity->addComponent<Transform2D>();
	}
	else m_collider = &m_entity->getComponent<Transform2D>().getRect();

	m_colliders.emplace_back(this);
}

void Collision::update() {
	/*for (auto& col : m_colliders) {
		if (col == this) continue;
		if (m_collider->intersects(col->getCollider())) {
			onCollisionEnter(*col);
		}
	}*/
}

void Collision::lateUpdate() {
	for (auto& col : m_colliders) {
		if (col == this) continue;
		if (m_collider->intersects(col->getCollider())) {
			onCollisionEnter(*col);
		}
	}
}

Rect<float> Collision::getCollider() {
	return *m_collider;
}

void Collision::onCollisionEnter(Collision& col) {
	m_entity->onCollisionEnter(col);
}