#include "TextureManager.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

TextureManager* TextureManager::m_instance = nullptr;

TextureManager::TextureManager() {
	if (!m_instance) {
		m_instance = this;
	}
	loadTilesets();
}

TextureManager::~TextureManager() {

}

void TextureManager::loadBackground() {
	m_background[0].loadFromFile("");
}

void TextureManager::loadTilesets() {
	m_tilesets[TileSetType::Block_Type].loadFromFile("Resources/blocks.png");
}