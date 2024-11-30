#include "Object.hpp"
#include "GameManager.hpp"
#include "ECS.hpp"
#include "Transform2D.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

Object::Object(Object* parent) : m_transform(addComponent<Transform2D>()), m_parent(parent) {
	EntitiesManager::addEntity(this);
	m_active = true;
}

Object::Object(const Object& obj) : Object() {
	m_parent = obj.m_parent;
	m_renderOrder = obj.m_renderOrder;
	m_transform = obj.m_transform;
}

Object::~Object() {
	EntitiesManager::removeEntity(this);
}

Object* Object::clone() {
	return new Object(*this);
}

bool Object::isActive() {
	return (!m_parent || m_parent->isActive()) && m_active;
}

Object* Object::getParent() {
	return m_parent;
}

void Object::setParent(Object* parent) {
	m_parent = parent;
}

Transform2D& Object::getTransform2D() {
	return m_transform;
}

void Object::setRenderOrder(int order) {
	m_renderOrder = order;
}

void Object::update() {
	
}

void Object::render() {
	
}

void Object::destroy() {
	m_active = false;
}