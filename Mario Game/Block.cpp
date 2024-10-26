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

Block::Block(int id) {
	m_id = id;

	Texture& texture = TextureManager::m_instance->m_tilesets[TileSetType::Block_Type];
	m_sprite.setTexture(texture, { int(m_id % (texture.getSize().x / 16) * 16), int(m_id / (texture.getSize().x / 16) * 16), 16, 16 });

	m_physics2D = &addComponent<Physics2D>();
	m_collision = &addComponent<Collision>();

	m_physics2D->setStatic(true);
	m_physics2D->setFriction(1.0f);

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;
}

Block::~Block() {

}

void Block::update() {
	
}