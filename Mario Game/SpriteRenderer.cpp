#include "ECS.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
#include "Object.hpp"
using namespace sf;

SpriteRenderer::SpriteRenderer(Object* parent) : Object(parent) {
	m_renderOrder = 0;
	Object::m_transform.setAnchor(0, 0);
}

SpriteRenderer::~SpriteRenderer() {
	
}

void SpriteRenderer::update() {
	Vector2f anchor = Object::m_transform.getAnchor();

	setOrigin(getLocalBounds().width * anchor.x, getLocalBounds().height * anchor.y);
	Sprite::setPosition(Object::m_transform.getWorldPosition());
	if (m_parent) m_renderOrder = m_parent->getRenderOrder();
}

void SpriteRenderer::render() {
	GameManager::getInstance()->getRenderWindow().draw(*this);
}

Sprite& SpriteRenderer::getSprite() {
	return *this;
}

void SpriteRenderer::setTexture(const Texture& texture) {
	Sprite::setTexture(texture);
}

void SpriteRenderer::setTexture(const Texture& texture, const IntRect& rectangle) {
	Sprite::setTexture(texture, true);
	setTextureRect(rectangle);
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