#pragma once
#include "Block.hpp"
#include "TileSet.hpp"
#include "SpriteRenderer.hpp"
#include <vector>
using namespace std;

enum ItemType {
	OneUpMushroom,
	Coin,
	KoopaShell,
	BuzyShell,
	MagicMushroom,
	FireFlower,
	Starman
};

class Item : public Block {
private:
	SpriteRenderer m_sprite;
	ItemType m_type;
	bool m_isPlayAnim;
	float m_elapsedTime;
	int m_index;			// current index of m_anim
	vector<Frame> m_anim;

public:
	Item(Object* parent = nullptr);
	Item(ItemType type, Object* parent = nullptr);
	Item(const Item& item);
	~Item();

	void setAnim(vector<Frame>& anim);
	void addFrame();
	void playAnim();
	void stopAnim();

	void update() override;
	void render() override;
};