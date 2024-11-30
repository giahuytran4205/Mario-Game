#include "Item.hpp"
#include "Object.hpp"
#include "GameManager.hpp"

Item::Item(Object* parent) {
	m_sprite.setParent(this);
	m_transform.setAnchor(0, 0);
	m_collision = &addComponent<Collision>(true);
	m_elapsedTime = 0;
	m_index = 0;
	m_isPlayAnim = true;
	m_renderOrder = 1;
}

Item::Item(ItemType type, Object* parent) : Item(parent){
	m_type = type;

	m_transform.setSize(16, 16);
}

Item::Item(const Item& item) {

}

Item::~Item() {

}

void Item::setAnim(vector<Frame>& anim) {
	m_anim = anim;
}

void Item::addFrame() {

}

void Item::playAnim() {

}

void Item::stopAnim() {

}

void Item::update() {
	if (m_isPlayAnim) {
		if (m_elapsedTime <= 0) {
			m_elapsedTime = m_anim[m_index].duration;
			m_sprite.setTexture(m_anim[m_index].texture);
			m_index++;
			m_index %= m_anim.size();
		}
		else m_elapsedTime -= deltaTime.asMilliseconds();
	}
}

void Item::render() {
	
}