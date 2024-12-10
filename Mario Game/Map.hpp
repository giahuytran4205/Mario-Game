#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TileSet.hpp"
#include "Block.hpp"
#include "Portal.hpp"
#include "FlagPole.hpp"
#include "Beanstalk.hpp"
#include "DeadZone.hpp"
#include "Jumper.hpp"
#include "Coin.hpp"
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
	Vector2f m_spawnPos;
	Vector2f m_castleGate;
	vector<Object*> m_objects;
	vector<pair<int, TileSet&>> m_tilesets;

	void loadTilesets(json::object& data);
	const Texture& getTile(int id);

public:
	Map();
	Map(const string& filename);
	~Map();

	void render() override;
	void setBackground(const Texture& texture);
	void loadFromJsonFile(const string& filename);
	Vector2i getSize() const;
	int rowCount() const;
	int colCount() const;
	int getCurrentDepth() const;
	Vector2f getSpawnPos() const;
};