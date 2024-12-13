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

Block::Block(Object* parent) : m_physics2D(addComponent<Physics2D>()) {
	addComponent<Collision>();
	setParent(parent);
	m_renderOrder = 2;

	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setParent(this);
	m_sprite.setRenderOrder(2);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);

	m_physics2D.setStatic(true);

	m_environment = Environment::OVERWORLD;
	m_isHide = false;
}

Block::Block(const Vector2f& pos) : Block() {
	m_transform.setSize(16, 16);
	m_transform.setPosition(pos);
}

Block::Block(const Texture& texture, const Vector2f& pos) : Block(pos) {
	m_sprite.setTexture(texture);
}

Block::Block(const Block& block) : Block(block.getParent()) {

}

Block::~Block() {

}

Block& Block::operator=(const Block& block) {
	m_physics2D = block.m_physics2D;
	m_sprite = block.m_sprite;
	return *this;
}

void Block::update() {
	
}

void Block::onHit(bool isDestroy) {
	m_physics2D.bounce(-0.09f);
}