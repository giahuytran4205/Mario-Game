#pragma once
#include "SFML/Graphics.hpp"
#include <boost/json.hpp>
using namespace std;
using namespace sf;
namespace json = boost::json;

struct Frame {
	Texture* frame;
	int duration;
};

struct Tile {
	Tile(const Texture& texture, const string& type = "", const bool& isAnim = false);
	Texture texture;
	bool isAnim;
	vector<Frame> anim;
	string type;
};

class TileSet {
public:
	vector<Tile> m_tiles;
	int m_row, m_col, m_tilesize;
	json::object readJsonFile(string filename);

public:
	TileSet();
	TileSet(string filename);
	TileSet(const TileSet& tileset);
	~TileSet();

	Tile& operator[](const int& id);
	void loadFromJsonFile(string filename);
};