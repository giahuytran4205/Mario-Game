#include "Block.hpp"
#include "TextureManager.hpp"
#include <iostream>

Block::Block(int id) {
	m_id = id;

	Texture& texture = TextureManager::m_instance->m_tilesets[TileSetType::Block_Type];
	m_sprite.setTexture(texture, true);

	m_sprite.setTextureRect({ int(m_id % (texture.getSize().x / 16) * 16), int(m_id / (texture.getSize().x / 16) * 16), 16, 16 });

	m_physics2D = &addComponent<Physics2D>();
	m_collision = &addComponent<Collision>();

	m_physics2D->setStatic(true);
	m_physics2D->setFriction(1.0f);

	m_transform.getRect().width = 16;
	m_transform.getRect().height = 16;
}

Block::~Block() {

}

void Block::Update() {
	m_sprite.setPosition(m_transform.getPosition());
}