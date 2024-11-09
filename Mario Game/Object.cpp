#include "Object.hpp"
#include "GameManager.hpp"
#include "ECS.hpp"
#include "Transform2D.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

Object::Object(Object* parent) : m_transform(addComponent<Transform2D>()), m_sprite(addComponent<SpriteRenderer>()), m_parent(parent) {
	EntitiesManager::addEntity(this);
	m_active = true;
	m_renderLayer = 0;
}

Object::~Object() {

}

bool Object::isActive() {
	return m_active;
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

void Object::setRenderLayer(int layer) {
	m_renderLayer = layer;
}

void Object::setTexture(Texture& texture) {
	m_sprite.setTexture(texture);
}

void Object::loadTexture(string filename) {
	//m_texture.loadFromFile(filename);
	//m_sprite.setTexture(m_texture);
}

void Object::update() {
	
}

void Object::render() {
	
}

void Object::destroy() {
	m_active = false;
}