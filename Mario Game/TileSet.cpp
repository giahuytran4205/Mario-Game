#include "TileSet.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/json.hpp>
namespace json = boost::json;
using namespace std;

//Frame::Frame(Texture& frame, const int& duration) : frame(frame), duration(duration) {}

Tile::Tile(const Texture& texture, const string& type, const bool& isAnim) : texture(texture), type(type), isAnim(isAnim) {}

json::object TileSet::readJsonFile(string filename) {
	ifstream fIn(filename);

	if (!fIn) {
		cerr << "Cannot open file!";
		return {};
	}

	string jsonContent((istreambuf_iterator<char>(fIn)), std::istreambuf_iterator<char>());

	json::value parsed = json::parse(jsonContent);
	return parsed.as_object();
}

TileSet::TileSet() {
	m_row = m_col = m_tilesize = 0;
}

TileSet::TileSet(string filename) {
	loadFromJsonFile(filename);
}

TileSet::TileSet(const TileSet& tileset) {
	m_row = tileset.m_row;
	m_col = tileset.m_col;
	m_tilesize = tileset.m_tilesize;
	m_tiles = tileset.m_tiles;
}

TileSet::~TileSet() {

}

Tile& TileSet::operator[](const int& id) {
	return m_tiles[id];
}

void TileSet::loadFromJsonFile(string filename) {
	json::object parsed = readJsonFile(filename);

	string imagePath = parsed["image"].as_string().c_str();
	m_col = parsed["columns"].as_int64();
	int imageHeight = parsed["imageheight"].as_int64();
	int imageWidth = parsed["imagewidth"].as_int64();
	int tilecount = parsed["tilecount"].as_int64();
	int tileWidth = imageWidth / m_col;
	int tileHeight = parsed["tileheight"].as_int64();
	m_row = imageHeight / tileHeight;

	json::array tiles = parsed["tiles"].as_array();

	Image tileset;
	tileset.loadFromFile(imagePath);

	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			Texture texture;
			texture.loadFromImage(tileset, IntRect(j * 16, i * 16, 16, 16));
			Tile tile(texture);
			m_tiles.push_back(tile);
		}
	}

	for (auto& item : tiles) {
		auto& obj = item.as_object();
		int id = obj["id"].as_int64();

		m_tiles[id].type = obj["properties"].as_array().front().as_object()["value"].as_string().c_str();

		if (obj.if_contains("animation")) {
			for (auto& frame : obj["animation"].as_array()) {
				auto& frameObj = frame.as_object();

				int duration = frameObj["duration"].as_int64();
				int tileID = frameObj["tileid"].as_int64();

				m_tiles[id].anim.push_back({ &m_tiles[tileID].texture, duration });
			}
		}
	}
}