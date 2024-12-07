#include "GUI.hpp"
#include "Slider.hpp"
#include <iostream>

Handle::Handle(Object* parent) : m_handleShape(5, 500) {
	m_parent = parent;
	m_transform.setParent(parent);
	m_transform.getRect() = { 0, 0, 20, 20 };
	m_handleShape.setFillColor(Color(150, 150, 150));
	m_handleShape.setOutlineThickness(3);
	m_handleShape.setOutlineColor(Color(70, 70, 70));
}

Handle::~Handle() {
	
}

void Handle::update() {
	m_handleShape.setPosition(m_transform.getWorldPosition() - Vector2f(m_handleShape.getRadius(), m_handleShape.getRadius()));
	if (isOnDrag()) {
		m_handleShape.setFillColor(Color(100, 100, 100));
		m_handleShape.setOutlineColor(Color(20, 20, 20));
	}
	else {
		m_handleShape.setFillColor(Color(150, 150, 150));
		m_handleShape.setOutlineColor(Color(70, 70, 70));
	}
}

void Handle::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_handleShape);
}

void Handle::onDrag(const Vector2f& mousePos) {
	m_dragPos = mousePos;
}

const Vector2f& Handle::getDragPos() {
	return m_dragPos;
}

void Handle::setColor(const Color& color) {
	m_handleShape.setFillColor(color);
}

void Handle::setOutlineColor(const Color& color) {
	m_handleShape.setOutlineColor(color);
}

void Handle::setThickness(float thickness) {
	m_handleShape.setOutlineThickness(thickness);
}