#include "Transform2D.hpp"
#include "Rect.hpp"
#include <cmath>

Vector2f Transform2D::getPosition() {
	return { m_x, m_y };
}

void Transform2D::setPosition(float x, float y) {
	m_lastX = m_x;
	m_lastY = m_y;
	m_x = x;
	m_y = y;
	m_rect.setPosition({ m_x, m_y });
}

void Transform2D::setPosition(const Vector2f& position) {
	m_lastX = m_x;
	m_lastY = m_y;
	m_x = position.x;
	m_y = position.y;
	m_rect.setPosition(position);
}

Vector2f Transform2D::getLastPosition() {
	return { m_lastX, m_lastY };
}

Vector2f Transform2D::getRotation() {
	return m_rotation;
}

void Transform2D::setRotation(const Vector2f& rotation) {
	m_rotation = rotation;
}

void Transform2D::setRotation(const float& angle) {
	m_rotation = { cos(angle * PI / 180), -sin(angle * PI / 180) };
}

void Transform2D::move(float dx, float dy) {
	m_lastX = m_x;
	m_lastY = m_y;
	m_x += dx;
	m_y += dy;
	m_rect.setPosition({ m_x, m_y });
}

gr::Rect& Transform2D::getRect() {
	return m_rect;
}


void Transform2D::move(Vector2f d) {
	m_lastX = m_x;
	m_lastY = m_y;
	m_x += d.x;
	m_y += d.y;
	m_rect.setPosition({ m_x, m_y });
}

Vector2f normalize(const Vector2f& v) {
	if (v.x == 0 && v.y == 0)
		return v;

	float magnitude = sqrt(v.x * v.x + v.y * v.y);
	return { v.x / magnitude, v.y / magnitude };
}