#include "Item.hpp"
#include "Object.hpp"
#include "GameManager.hpp"

Item::Item(Object* parent) : m_anim(addComponent<Animation>(m_sprite)) {
	m_sprite.setParent(this);
	addComponent<Collision>(true);
	m_transform.setAnchor(0, 0);
	m_renderOrder = 1;
}

Item::~Item() {

}

void Item::update() {
	
}

void Item::render() {
	
}