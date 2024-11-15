#include "Map.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include "Item.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

Map::Map() {
	m_width = m_height = 0;
}

Map::~Map() {

}

json::object Map::readJsonFile(string filename) {
	ifstream fIn(filename);

	if (!fIn) {
		cerr << "Cannot open file!";
		return {};
	}

	string jsonContent((istreambuf_iterator<char>(fIn)), std::istreambuf_iterator<char>());

	json::value parsed = json::parse(jsonContent);
	return parsed.as_object();
}

void Map::loadFromJsonFile(string filename) {
	json::object parsed = readJsonFile(filename);
	
	m_col = parsed["width"].as_int64();
	m_row = parsed["height"].as_int64();
	m_tileWidth = parsed["tilewidth"].as_int64();
	m_tileHeight = parsed["tileheight"].as_int64();
	m_width = m_tileWidth * m_col;
	m_height = m_tileHeight * m_row;

	for (auto& item : parsed["layers"].as_array()) {
		auto& layer = item.as_object();
		if (layer["name"] == "Graphics Layer") {
			for (int i = 0; i < layer["data"].as_array().size(); i++) {
				int id = layer["data"].as_array()[i].as_int64() - 1;
				if (id == -1 || id >= TextureManager::m_instance->m_tilesets[0].m_tiles.size()) continue;
				Tile& tile = TextureManager::m_instance->m_tilesets[0][id];
				int col = TextureManager::m_instance->m_tilesets[0].m_col;
				if (tile.type == "Coin") {
					Item* item = new Item(ItemType::Coin);
					item->setAnim(tile.anim);
					item->getComponent<Transform2D>().setPosition({ i % 216 * 16.0f + 8, i / 216 * 16.0f + 8 });
				}
				else {
					bool isAddCollision = tile.type == "Ground" || tile.type == "Pipe" || tile.type == "StairBlock" || tile.type == "QuestionBlock" || tile.type == "EmptyBlock" || tile.type == "Brick";
					Block* block = new Block(tile.texture, { i % 216 * 16.0f + 8, i / 216 * 16.0f + 8 }, isAddCollision);
					m_blocks.push_back(block);
				}
			}
		}

		if (layer["name"] == "Teleportation Gate") {
			for (int i = 0; i < layer["objects"].as_array().size(); i++) {

			}
		}
	}
}

void Map::setBackground(const Texture& texture) {
	m_background.setTexture(texture);
}

Vector2i Map::getSize() const {
	return { m_width, m_height };
}

int Map::rowCount() const {
	return m_row;
}

int Map::colCount() const {
	return m_col;
}

void Map::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}