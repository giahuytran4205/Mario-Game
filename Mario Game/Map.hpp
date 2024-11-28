#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "Block.hpp"
#include "Portal.hpp"
#include <boost/json.hpp>
using namespace sf;
namespace json = boost::json;

class Map : public Object {
private:
	SpriteRenderer m_background;
	int m_row;
	int m_col;
	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	int m_curDepth;
	vector<Block*> m_blocks;
	vector<Portal*> m_portals;
	json::object readJsonFile(string filename);

public:
	Map();
	~Map();

	void setBackground(const Texture& texture);
	void loadFromJsonFile(string filename);
	Vector2i getSize() const;
	int rowCount() const;
	int colCount() const;
	int getCurrentDepth() const;
	void render() override;
};