#include "DeadZone.hpp"

DeadZone::DeadZone(Object* parent) {
	setParent(parent);
	addComponent<Collision>(true);
}

DeadZone::DeadZone(const FRect& rect, Object* parent) : DeadZone(parent) {
	m_transform.setSize(rect.width, rect.height);
	m_transform.setPosition(rect.left, rect.top);
}

DeadZone::~DeadZone() {}

void DeadZone::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>()) {
		Mario* mario = col.m_entity->convertTo<Mario>();
		if (!mario->isDead())
			mario->dead();
	}
}