#include "Item.hpp"
#include "Object.hpp"
#include "AutoControl.hpp"
#include "GameManager.hpp"

Item::Item(Object* parent) : m_anim(addComponent<Animation>(m_sprite)), m_physics(addComponent<Physics2D>()), m_autoControl(addComponent<AutoControl>()) {
	setParent(parent);
	addComponent<Collision>(true);
	m_transform.setAnchor(0, 0);

	m_sprite.setParent(this);
	
	m_renderOrder = 1;
	m_direction = Direction::LEFT;
	m_speed = 0;
}

Item::~Item() {

}

void Item::update() {
	
}

void Item::render() {
	
}

void Item::setDirection(const Direction& direction) {
	m_direction = direction;
}

void Item::appear() {}