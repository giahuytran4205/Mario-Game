#include "Item.hpp"
#include "GameManager.hpp"

Item::Item(Object* parent) {

}

Item::Item(ItemType type, Object* parent) : m_type(type), m_isPlayAnim(true) {
	m_parent = parent;
	m_elapsedTime = 0;
	m_index = 0;
	m_collision = &addComponent<Collision>();

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;
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