#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class TextureManager {
public:
	static TextureManager* m_instance;
	Texture m_background[NUM_STATE];
	Texture m_tilesets[TileSetType::NUM_TILESET_TYPE];

	TextureManager();
	~TextureManager();

	void loadBackground();
	void loadTilesets();
};