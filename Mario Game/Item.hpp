#pragma once
#include "Block.hpp"
#include "TileSet.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"
#include <vector>
using namespace std;

class Item : public Object {
protected:
	SpriteRenderer m_sprite;
	Animation& m_anim;

public:
	Item(Object* parent = nullptr);
	~Item();

	void update() override;
	void render() override;
};