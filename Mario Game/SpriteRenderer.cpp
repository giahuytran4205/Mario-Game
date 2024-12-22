#include "ECS.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
using namespace sf;

SpriteRenderer::SpriteRenderer(Object* parent) : Object(parent) {
	Object::m_transform.setAnchor(0, 0);
	if (m_parent)
		m_renderOrder = m_parent->getRenderOrder();
}

SpriteRenderer::~SpriteRenderer() {
	
}

SpriteRenderer& SpriteRenderer::operator=(const SpriteRenderer& other) {
	Sprite::operator=(other);
	Object::operator=(other);
	return *this;
}

void SpriteRenderer::update() {
	Vector2f anchor = Object::m_transform.getAnchor();

	setOrigin(getLocalBounds().width * anchor.x, getLocalBounds().height * anchor.y);
	Sprite::setPosition(Object::m_transform.getWorldPosition());
}

void SpriteRenderer::render() {
	GameManager::getInstance()->getRenderWindow().draw(*this);
}

Sprite& SpriteRenderer::getSprite() {
	return *this;
}

void SpriteRenderer::setPosition(const Vector2f& pos) {
	Object::m_transform.setPosition(pos);
}

void SpriteRenderer::setPosition(float x, float y) {
	setPosition({ x, y });
}

void SpriteRenderer::setAnchor(const Vector2f& anchor) {
	Object::m_transform.setAnchor(anchor);
}

void SpriteRenderer::setAnchor(float anchorX, float anchorY) {
	setAnchor({ anchorX, anchorY });
}