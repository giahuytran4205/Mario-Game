#include "TextureManager.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

TextureManager* TextureManager::m_instance = nullptr;

void TextureManager::loadBackground() {
	m_background[BackgroundType::LOGINSTATE_BACKGROUND].loadFromFile("Resources/Background/860645.png");
}

void TextureManager::loadTilesets() {
	m_tilesets[TileSetType::BLOCK].loadFromJsonFile("Resources/Map/Tileset-1.json");
	//m_tilesets[TileSetType::ITEM].loadFromJsonFile("Resources/TileSets/");
}

TextureManager::TextureManager() {
	if (!m_instance) {
		m_instance = this;
	}
	loadBackground();
	loadTilesets();
}

TextureManager::~TextureManager() {

}
