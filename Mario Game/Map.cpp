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
	for (Block* block : m_blocks)
		delete block;

	for (Portal* portal : m_portals)
		delete portal;
}

void Map::loadTilesets(json::object& data) {
	for (auto& i : data["tilesets"].as_array()) {
		json::object& obj = i.as_object();
		m_tilesets.push_back(pair<int, TileSet&>( obj["firstgid"].as_int64(), TextureManager::getTileset(obj["source"].as_string().c_str()) ));
	}
}

const Texture& Map::getTile(int id) {
	auto it = upper_bound(m_tilesets.begin(), m_tilesets.end(), pair<int, TileSet>{id, {}},
		[](const pair<int, TileSet>& a, const pair<int, TileSet>& b)
		{
			return a.first < b.first;
		});

	if (it == m_tilesets.begin())
		return {};

	--it;

	int numCols = it->second.getSize().x / m_tileWidth;

	id -= it->first;

	return it->second.getTile(IntRect(id % numCols * 16, id / numCols * 16, m_tileWidth, m_tileHeight));
}

void Map::loadFromJsonFile(string filename) {
	json::object parsed = readJsonFile(filename);
	
	loadTilesets(parsed);

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
				int id = layer["data"].as_array()[i].as_int64();

				if (id == 0) continue;
				Block* block = new Block(getTile(id), {i % m_col * 16.0f + 8, i / m_col * 16.0f + 8}, Block::TERRAIN);
				block->setParent(this);
				m_blocks.push_back(block);
			}
		}

		if (layer["name"] == "Background Layer") {
			string path = layer["image"].as_string().c_str();
			m_background.setTexture(TextureManager::getTexture(path));
		}

		if (layer["name"] == "Spawn Position") {
			json::object obj = layer["objects"].as_array()[0].as_object();
			m_spawnPos.x = obj["x"].as_int64();
			m_spawnPos.y = obj["y"].as_int64();
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
				m_portals.back()->setParent(this);
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

Vector2f Map::getSpawnPos() const {
	return m_spawnPos;
}

void Map::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}