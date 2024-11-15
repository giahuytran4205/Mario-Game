#include "Block.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "ECS.hpp"
#include "SpriteRenderer.hpp"
#include "Transform2D.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "Object.hpp"
#include <vector>
#include <iostream>
using namespace sf;

Block::Block() {
	m_id = 0;
}

Block::Block(Texture& texture, int x, int y) {
	m_sprite.setTexture(texture);

	m_physics2D = &addComponent<Physics2D>();
	//m_collision = &addComponent<Collision>();

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;

	m_transform.setPosition(x, y);
}

Block::Block(Texture& texture, const Vector2f& pos, bool addCollision) {
	m_sprite.setTexture(texture);

	m_physics2D = &addComponent<Physics2D>();
	if (addCollision) m_collision = &addComponent<Collision>();

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;

	m_transform.setPosition(pos);
}

Block::~Block() {

}

void Block::update() {
	
}

void Block::onHit(bool isDestroy) {
	m_physics2D->bounce(-0.7f);
}