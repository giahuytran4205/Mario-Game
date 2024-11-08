#include "TextureManager.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
using namespace std;
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
	m_tilesets[TileSetType::Block_Type].loadFromJsonFile("D:/GHuy/OOP/Tile/Tileset-1.json");
}