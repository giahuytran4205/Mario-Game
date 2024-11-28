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

Block::Block() : m_physics2D(addComponent<Physics2D>()) {
	m_renderOrder = 2;
	m_type = BlockType::EMPTY_BLOCK;

	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);

	m_collision = nullptr;
}

Block::Block(const Vector2f& pos, BlockType type) : Block() {
	if (type == BlockType::BRICK || type == BlockType::QUESTION_BLOCK || type == BlockType::TERRAIN)
		m_collision = &addComponent<Collision>();

	m_type = type;

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;

	m_transform.setPosition(pos);
}

Block::Block(Texture& texture, const Vector2f& pos, BlockType type) : Block(pos, type) {
	m_sprite.setTexture(texture);
}

Block::~Block() {

}

void Block::update() {
	
}

void Block::onHit(bool isDestroy) {
	m_physics2D.bounce(-0.09f);
}

Block::BlockType Block::getType() {
	return m_type;
}