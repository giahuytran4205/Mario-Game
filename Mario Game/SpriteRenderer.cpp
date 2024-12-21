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

	m_outline.setFillColor(Color::Transparent);
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

	if (getTexture()) {
		Vector2f size(getTexture()->getSize());
		m_outline.setSize(size);
		m_outline.setOrigin(Object::m_transform.getAnchor().x * size.x, Object::m_transform.getAnchor().y * size.y);
		m_outline.setPosition(Object::m_transform.getWorldPosition());
	}
}

void SpriteRenderer::render() {
	GameManager::getInstance()->getRenderWindow().draw(*this);
	if (m_outline.getOutlineThickness() != 0)
		GameManager::getInstance()->getRenderWindow().draw(m_outline);
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

void SpriteRenderer::setOutlineThickness(float thickness) {
	m_outline.setOutlineThickness(thickness);
}

void SpriteRenderer::setOutlineColor(const Color& color) {
	m_outline.setOutlineColor(color);
}