#include "Map.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include "Item.hpp"
#include "Portal.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

Map::Map() {
	m_width = m_height = 0;
	m_curDepth = 0;
	m_background.setParent(this);
	m_background.setPosition(0, 0);
	m_transform.getRect().setAnchor({ 0, 0 });
	m_renderOrder = 0;
}

Map::~Map() {
	/*for (Block* block : m_blocks)
		delete block;

	for (Portal* portal : m_portals)
		delete portal;*/
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
					item->getComponent<Transform2D>().setPosition({ i % 211 * 16.0f, i / 211 * 16.0f });
				}
				else {
					Block::BlockType type = Block::EMPTY_BLOCK;
					if (tile.type == "Ground" || tile.type == "Pipe" || tile.type == "StairBlock" || tile.type == "EmptyBlock")
						type = Block::TERRAIN;

					if (tile.type == "Brick")
						type = Block::BRICK;

					if (tile.type == "QuestionBlock")
						type = Block::QUESTION_BLOCK;

					if (tile.type == "SmallCloud")
						type = Block::SMALL_CLOUD;

					Block* block = new Block(tile.texture, { i % 211 * 16.0f + 8, i / 211 * 16.0f + 8 }, type);
					m_blocks.push_back(block);
				}
			}
		}

		if (layer["name"] == "Background Layer") {
			
		}

		if (layer["name"] == "Teleportation Gate") {
			for (auto& i : layer["objects"].as_array()) {
				auto& portal = i.as_object();

				int width = portal["width"].as_int64();
				int height = portal["height"].as_int64();

				float posX = portal["x"].as_int64();
				float posY = portal["y"].as_int64();

				float destX = 0, destY = 0, inDir = 0, outDir = 0, destDepth = 0;
				
				for (auto& j : portal["properties"].as_array()) {
					auto prop = j.as_object();

					if (prop["name"].as_string() == "destX")
						destX = prop["value"].as_int64();

					if (prop["name"].as_string() == "destY")
						destY = prop["value"].as_int64();

					if (prop["name"].as_string() == "inDirection")
						inDir = prop["value"].as_int64();

					if (prop["name"].as_string() == "outDirection")
						outDir = prop["value"].as_int64();

					if (prop["name"].as_string() == "destDepth")
						destDepth = prop["value"].as_int64();
				}

				m_portals.push_back(new Portal(Vector2f{ posX, posY }, Vector2f{ destX, destY }, inDir, outDir, destDepth));
			}
		}

		if (layer["name"] == "Flagpole") {
			
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

int Map::getCurrentDepth() const {
	return m_curDepth;
}

void Map::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}