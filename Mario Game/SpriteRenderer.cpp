#include "SpriteRenderer.hpp"
#include "ECS.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

SpriteRenderer::SpriteRenderer() {
	
}

SpriteRenderer::~SpriteRenderer() {

}

void SpriteRenderer::update() {
	if (m_entity->hasComponent<Transform2D>()) {
		Vector2f anchor = m_entity->getComponent<Transform2D>().getRect().getAnchor();
		m_sprite.setOrigin(m_sprite.getLocalBounds().width * anchor.x, m_sprite.getLocalBounds().height * anchor.y);
		Transform2D& transform = m_entity->getComponent<Transform2D>();
		m_sprite.setPosition(transform.getPosition());
	}
}

void SpriteRenderer::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_sprite);
}

Sprite& SpriteRenderer::getSprite() {
	return m_sprite;
}

void SpriteRenderer::setTexture(Texture& texture) {
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

void SpriteRenderer::setTexture(Texture& texture, const IntRect& rectangle) {
	m_sprite.setTexture(texture, true);
	m_sprite.setTextureRect(rectangle);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}