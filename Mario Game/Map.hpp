#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "Block.hpp"
#include <boost/json.hpp>
using namespace sf;
namespace json = boost::json;

class Map : public Object {
private:
	Sprite m_background;
	int m_row;
	int m_col;
	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	vector<Block*> m_blocks;
	json::object readJsonFile(string filename);

public:
	Map();
	~Map();

	void setBackground(const Texture& texture);
	void loadFromJsonFile(string filename);
	Vector2i getSize() const;
	int rowCount() const;
	int colCount() const;
	void render() override;
};