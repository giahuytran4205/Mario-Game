#include "SFML/Graphics.hpp"
#include "Block.hpp"
#include <string>
#include <vector>
using namespace sf;
using namespace std;

class Map : public Object {
private:
	Sprite m_background;
	vector<vector<int>> m_tilemap;
	vector<Block*> m_blocks;
public:
	Map();
	~Map();

	void setBackground(const Texture& texture);
	void loadBitmap(string filename);
	void drawMap();
	void render() override;
};