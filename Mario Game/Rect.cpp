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

bool FRect::contains(const sf::Vector2f& point) const {
	return left < point.x && top < point.y && right > point.x && bottom > point.y;
}

int FRect::tangentSide(const FRect& rect) const {
	if (rect.left == right)
		return 0;
	if (rect.bottom == top)
		return 1;
	if (rect.right == left)
		return 2;
	if (rect.top == bottom)
		return 3;

	return -1;
}

void FRect::setPosition(const sf::Vector2f& pos) {
	setPosition(pos.x, pos.y);
}

void FRect::setPosition(float x, float y) {
	left = x - m_anchor.x * width;
	top = y - m_anchor.y * height;
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

void FRect::setCenter(float x, float y) {
	setCenter({ x, y });
}

void FRect::setAnchor(const sf::Vector2f& anchor) {
	m_anchor = anchor;
}

void FRect::setAnchor(float anchorX, float anchorY) {
	setAnchor({ anchorX, anchorY });
}

void FRect::setSize(const sf::Vector2f& size) {
	setSize(size.x, size.y);
}

void FRect::setSize(float width, float height) {
	sf::Vector2f pos = getPosition();
	this->width = width;
	this->height = height;
	setPosition(pos);
}