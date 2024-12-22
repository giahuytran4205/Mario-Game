#include "TextureManager.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

map<string, TileSet> TextureManager::m_tilesets;
TextureManager* TextureManager::m_instance = nullptr;

TextureManager::TextureManager() {
	if (!m_instance) {
		m_instance = this;
	}
}

TextureManager::~TextureManager() {

}

TextureManager* TextureManager::getInstance() {
	return m_instance;
}

const Texture& TextureManager::getTexture(const string& filename) {
	return getTileset(filename).getTexture();
}

TileSet& TextureManager::getTileset(const string& filename) {
	if (!m_tilesets.contains(filename)) {
		m_tilesets[filename].loadFromFile(filename);
	}
	return m_tilesets[filename];
}

const Texture& TextureManager::getTile(string filename, const IntRect& rect, bool isRepeated) {
	return getTileset(filename).getTile(rect, isRepeated);
}