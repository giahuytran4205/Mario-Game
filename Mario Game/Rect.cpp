#include "Rect.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

FRect::FRect() {
	left = top = right = bottom = 0;
	width = height = 0;
	m_center = { 0, 0 };
}

FRect::FRect(float left, float top, float width, float height) {
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	right = left + width;
	bottom = top + height;
	m_center = { left + width / 2, top + height / 2 };
}

FRect::~FRect() {

}

sf::Vector2f FRect::getCenter() const {
	return m_center;
}

sf::Vector2f FRect::getPosition() const {
	return { left + m_anchor.x * width, top + m_anchor.y * height };
}

sf::Vector2f FRect::getAnchor() const {
	return m_anchor;
}

bool FRect::pointOverlap(const sf::Vector2f& point) const {
	return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}

void FRect::setPosition(const sf::Vector2f& pos) {
	left = pos.x - m_anchor.x * width;
	top = pos.y - m_anchor.y * height;
	right = left + width;
	bottom = top + height;
	m_center = { left + width / 2, top + height / 2 };
}

void FRect::setCenter(const sf::Vector2f& center) {
	m_center = center;
	left = center.x - width / 2;
	top = center.y - height / 2;
	right = left + width;
	bottom = right + height;
}

void FRect::setAnchor(const sf::Vector2f& anchor) {
	m_anchor = anchor;
}

void FRect::setSize(const sf::Vector2f& size) {
	sf::Vector2f pos = getPosition();
	width = size.x;
	height = size.y;
	setPosition(pos);
}