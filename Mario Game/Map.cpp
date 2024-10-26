#include "Map.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

Map::Map() {

}

Map::~Map() {

}

void Map::setBackground(const Texture& texture) {
	m_background.setTexture(texture);
}

void Map::loadBitmap(string filename) {
	fstream fIn(filename, ios::in);
	if (!fIn) {
		cout << "Cannot open file " << filename << '\n';
		return;
	}

	string line;
	while (getline(fIn, line)) {
		stringstream ss(line);
		m_tilemap.push_back(vector<int>());
		int id;
		string buf;
		while (getline(ss, buf, ',')) {
			m_tilemap.back().push_back(stoi(buf));
		}
	}
}

void Map::drawMap() {
	for (int i = 0; i < m_tilemap.size(); i++) {
		for (int j = 0; j < m_tilemap[i].size(); j++) {
			if (m_tilemap[i][j] == -1) continue;
			m_blocks.push_back(new Block(m_tilemap[i][j]));
			m_blocks.back()->getTransform2D().setPosition({ 16.0f * j + 8, 16.0f * i + 8 });
		}
	}
}

void Map::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}