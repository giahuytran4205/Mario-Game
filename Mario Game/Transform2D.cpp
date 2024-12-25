#include "Transform2D.hpp"
#include "Rect.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"
#include <cmath>
using namespace sf;

#if DEBUG

VertexArray Transform2D::rectangles(Lines);

void Transform2D::render() {
	rectangles.append(Vertex(Vector2f(left, top), Color::Red));
	rectangles.append(Vertex(Vector2f(right, top), Color::Red));

	rectangles.append(Vertex(Vector2f(right, top), Color::Red));
	rectangles.append(Vertex(Vector2f(right, bottom), Color::Red));

	rectangles.append(Vertex(Vector2f(right, bottom), Color::Red));
	rectangles.append(Vertex(Vector2f(left, bottom), Color::Red));

	rectangles.append(Vertex(Vector2f(left, bottom), Color::Red));
	rectangles.append(Vertex(Vector2f(left, top), Color::Red));
}

#endif // DEBUG

Transform2D::Transform2D() {
	
#if DEBUG
	m_shape.setOutlineThickness(0.5);
	m_shape.setFillColor(Color::Transparent);
	m_shape.setOutlineColor(Color::Red);
#endif // DEBUG

	m_firstSetPos = true;
}

Transform2D::~Transform2D() {}

void Transform2D::init() {
	m_parent = m_entity->toObject()->getParent();
}

Vector2f Transform2D::getPosition() {
	m_parent = m_entity->toObject()->getParent();
	if (!m_parent)
		return FRect::getPosition();
	return m_parent->getComponent<Transform2D>().transformPoint(FRect::getPosition());
}

void Transform2D::setPosition(float x, float y) {
	setPosition({ x, y });
}

void Transform2D::setPosition(const Vector2f& position) {
	m_parent = m_entity->toObject()->getParent();

	if (getPosition() != position) m_lastPos = getPosition();
	m_pos = position;
	if (m_parent)
		FRect::setPosition(m_parent->getComponent<Transform2D>().reverseTransformPoint(position));
	else
		FRect::setPosition(position);
	
	if (m_firstSetPos) {
		m_firstSetPos = false;
		m_lastPos = m_pos;
	}
}

void Transform2D::setWorldPosition(const Vector2f& position) {
	m_parent = m_entity->toObject()->getParent();

	if (getWorldPosition() != position) {
		m_lastPos = getPosition();
	}
	
	if (m_parent)
		m_pos = m_parent->getComponent<Transform2D>().transformPoint(position);
	else
		m_pos = position;

	FRect::setPosition(position);

	if (m_firstSetPos) {
		m_firstSetPos = false;
		m_lastPos = m_pos;
	}
}

void Transform2D::setWorldPosition(float x, float y) {
	setWorldPosition({ x, y });
}

void Transform2D::setCenter(const Vector2f& center) {
	m_parent = m_entity->toObject()->getParent();
	setWorldPosition(center - getCenter() + getWorldPosition());
}

void Transform2D::setCenter(float x, float y) {
	setCenter({ x, y });
}

Vector2f Transform2D::getLastPosition() {
	m_parent = m_entity->toObject()->getParent();
	if (m_parent) {
		return m_lastPos + m_parent->getComponent<Transform2D>().getWorldPosition();
	}
	return m_lastPos;
}

Vector2f Transform2D::getRotation() {
	return m_rotation;
}

Vector2f Transform2D::getWorldPosition() {
	return FRect::getPosition();
}

Vector2f Transform2D::getLastCenter() {
	m_parent = m_entity->toObject()->getParent();
	return getLastPosition() + transformPoint(getWorldCenter());
}

Vector2f Transform2D::getCenter() {
	m_parent = m_entity->toObject()->getParent();
	if (!m_parent)
		return FRect::getCenter();
	return m_parent->getComponent<Transform2D>().transformPoint(FRect::getCenter());
}

Vector2f Transform2D::getWorldCenter() {
	return FRect::getCenter();
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
	m_parent = m_entity->toObject()->getParent();
	if (m_parent)
		FRect::setPosition(m_parent->getComponent<Transform2D>().transformPoint(pos));
	else
		FRect::setPosition(pos);

	m_pos = getPosition();
}

void Transform2D::adjustCenter(const Vector2f& center) {
	m_parent = m_entity->toObject()->getParent();
	adjustPosition(center - getCenter() + getWorldPosition());
}

void Transform2D::adjustCenter(float centerX, float centerY) {
	adjustCenter({ centerX, centerY });
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
	Vector2f worldPos = getWorldPosition();

	if (m_parent != m_entity->toObject()->getParent()) {
		m_parent = m_entity->toObject()->getParent();
		//setWorldPosition(worldPos);
	}

	if (m_parent)
		setPosition(m_pos);
}

void Transform2D::setRect(const FRect& rect) {
	setWorldPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
	m_pos = getPosition();
}

void Transform2D::setRect(float left, float top, float width, float height) {
	setRect(FRect(left, top, width, height));
}

void Transform2D::setParent(Object* parent) {
	m_parent = parent;
	if (m_parent) setPosition(m_parent->getComponent<Transform2D>().transformPoint(getPosition()));
}