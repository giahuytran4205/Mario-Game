#include "Transform2D.hpp"
#include "Rect.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include "Transform2D.hpp"
#include <cmath>
using namespace sf;

Transform2D::Transform2D() {
	if (m_entity) m_parent = m_entity->toObject()->getParent();
	else m_parent = nullptr;
}

Transform2D::~Transform2D() {}

Vector2f Transform2D::getPosition() {
	return m_pos;
}

void Transform2D::setPosition(float x, float y) {
	setPosition({ x, y });
}

void Transform2D::setPosition(const Vector2f& position) {
	if (m_lastPos == m_pos && m_pos == Vector2f(0, 0)) {
		m_lastPos = m_pos = position;
		FRect::setPosition(getWorldPosition());
	}
	if (m_pos != position) m_lastPos = m_pos;
	m_pos = position;
	FRect::setPosition(getWorldPosition());
}

void Transform2D::setCenter(const Vector2f& center) {
	setPosition(center - getSize() / 2.0f);
}

void Transform2D::setCenter(float x, float y) {
	setCenter({ x, y });
}

Vector2f Transform2D::getLastPosition() {
	return m_lastPos;
}

Vector2f Transform2D::getRotation() {
	return m_rotation;
}

Vector2f Transform2D::getWorldPosition() {
	if (m_parent) {
		return m_parent->getComponent<Transform2D>().getWorldPosition() + m_pos;
	}
	return m_pos;
}

void Transform2D::setRotation(const Vector2f& rotation) {
	m_rotation = rotation;
}

void Transform2D::setRotation(float angle) {
	m_rotation = { cos(angle * PI / 180), -sin(angle * PI / 180) };
}

void Transform2D::move(float dx, float dy) {
	move({ dx, dy });
}

void Transform2D::move(const Vector2f& d) {
	m_lastPos = m_pos;
	m_pos += d;
	FRect::setPosition(getWorldPosition());
}

FRect& Transform2D::getRect() {
	return *this;
}

void Transform2D::adjustPosition(const Vector2f& pos) {
	m_pos = pos;
	FRect::setPosition(getWorldPosition());
}

Vector2f Transform2D::transformPoint(const Vector2f& point) {
	return point - getWorldPosition();
}

Vector2f Transform2D::transformPoint(float x, float y) {
	return transformPoint({ x, y });
}

Vector2f Transform2D::reverseTransformPoint(const Vector2f& point) {
	return point + getWorldPosition();
}

Vector2f Transform2D::reverseTransformPoint(float x, float y) {
	return reverseTransformPoint({ x, y });
}

void Transform2D::update() {
	m_parent = m_entity->toObject()->getParent();
}

void Transform2D::setParent(Object* parent) {
	m_parent = parent;
	if (m_parent) setPosition(m_parent->getComponent<Transform2D>().transformPoint(getPosition()));
}