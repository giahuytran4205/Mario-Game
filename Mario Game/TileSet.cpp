#include "TileSet.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/json.hpp>
namespace json = boost::json;
using namespace std;

Tile::Tile(const Texture& texture, const string& type, const bool& isAnim) : texture(texture), type(type), isAnim(isAnim) {}

TileSet::TileSet() {
	
}

TileSet::~TileSet() {

}

bool TileSet::loadFromFile(const string& filename) {
	bool ok = m_tileset.loadFromFile(filename);
	m_size = m_tileset.getSize();
	return ok;
}

const Vector2u& TileSet::getSize() {
	return m_size;
}

const Texture& TileSet::getTile(const IntRect& rect, bool isRepeated) {
	if (!m_tiles.contains(pair{ rect, isRepeated })) {
		m_tiles[pair{ rect, isRepeated }].loadFromImage(m_tileset, rect);
		m_tiles[pair{ rect, isRepeated }].setRepeated(isRepeated);
	}
	return m_tiles[pair{ rect, isRepeated }];
}

const Texture& TileSet::getTexture() {
	return getTile(IntRect(0, 0, m_tileset.getSize().x, m_tileset.getSize().y));
}