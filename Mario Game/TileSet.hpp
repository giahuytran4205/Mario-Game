#pragma once
#include "SFML/Graphics.hpp"
#include <boost/json.hpp>
using namespace std;
using namespace sf;
namespace json = boost::json;

namespace sf {
	inline bool operator<(const IntRect& a, const IntRect& b) {
		if (a.left != b.left)
			return a.left < b.left;

		if (a.top != b.top)
			return a.top < b.top;

		if (a.width != b.width)
			return a.width < b.width;

		if (a.height != b.height)
			return a.height < b.height;

		return false;
	}
}

struct Frame {
	Texture texture;
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
private:
	Image m_tileset;
	Vector2u m_size;
	map<pair<IntRect, bool>, Texture> m_tiles;

public:
	TileSet();
	~TileSet();

	bool loadFromFile(const string& filename);
	const Vector2u& getSize();
	const Texture& getTile(const IntRect& rect, bool isRepeated = false);
	const Texture& getTexture();
};