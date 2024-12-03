#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TileSet.hpp"
#include <map>
#include <boost/json.hpp>
using namespace sf;
namespace json = boost::json;

class TextureManager {
private:
	static map<string, TileSet> m_tilesets;
	static TextureManager* m_instance;

public:
	TextureManager();
	~TextureManager();

	TextureManager* getInstance();
	static const Texture& getTexture(const string& filename);
	static TileSet& getTileset(const string& filename);
	static const Texture& getTile(string filename, const IntRect& rect = { 0, 0, 0, 0 }, bool isRepeated = false);
};