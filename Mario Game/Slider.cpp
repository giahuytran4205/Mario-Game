#include "GUI.hpp"
#include "Slider.hpp"
#include <iostream>

Handle::Handle() {

}

Handle::Handle(RenderWindow& window, Object* parent) : m_handleShape(7, 500) {
	m_window = &window;
	m_parent = parent;
	m_transform.setParent(parent);
	m_transform.getRect() = { 0, 0, 20, 20 };
	m_handleShape.setFillColor(Color::Red);
}

Handle::~Handle() {
	
}

void Handle::update() {
	m_handleShape.setPosition(m_transform.getWorldPosition() - Vector2f(m_handleShape.getRadius(), m_handleShape.getRadius()));
}

void Handle::render() {
	m_window->draw(m_handleShape);
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