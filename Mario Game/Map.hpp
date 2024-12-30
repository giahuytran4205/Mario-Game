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
#include "Lift.hpp"
#include "Mario.hpp"
#include <boost/json.hpp>
using namespace sf;
namespace json = boost::json;

struct MapInfo {
	MapInfo(const string& name, const string& path, const string& thumbnailPath) : name(name), path(path) {
		thumbnail.loadFromFile(thumbnailPath);
	}

	string name;
	string path;
	Texture thumbnail;
};

class Map : public Object {
private:
	SpriteRenderer m_background;
	int m_row;
	int m_col;
	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	int m_startDepth;
	Vector2f m_spawnPos;
	Vector2f m_castleGate;
	FRect m_fireworkArea;
	vector<Object*> m_objects;
	vector<pair<int, TileSet&>> m_tilesets;

	Mario& m_mario;

	void loadTilesets(json::object& data);
	const Texture& getTile(int id);
	void loadObjectInGroup(Environment environment, json::object& group);

public:
	static const vector<MapInfo> mapsInfo;

public:
	Map(Mario& mario);
	Map(const string& filename, Mario& mario);
	~Map();

	void render() override;
	void setBackground(const Texture& texture);
	void loadFromJsonFile(const string& filename);
	Vector2i getSize() const;
	int rowCount() const;
	int colCount() const;
	int getStartDepth() const;
	Vector2f getSpawnPos() const;
	Vector2f getCastleGate() const;
	FRect getFireworkArea() const;
	void launchFireworks();
};