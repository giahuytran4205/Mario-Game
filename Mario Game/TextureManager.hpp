#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TileSet.hpp"
#include <boost/json.hpp>
using namespace sf;
namespace json = boost::json;

class TextureManager {
public:
	static TextureManager* m_instance;
	Texture m_background[BackgroundType::NUM_BACKGROUND_TYPE];
	TileSet m_tilesets[TileSetType::NUM_TILESET_TYPE];

	TextureManager();
	~TextureManager();

	void loadBackground();
	void loadTilesets();
};