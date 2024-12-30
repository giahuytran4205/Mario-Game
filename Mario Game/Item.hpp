#pragma once
#include "Block.hpp"
#include "TileSet.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"
#include "AutoControl.hpp"
#include <vector>
using namespace std;

class Item : public Object {
protected:
	SpriteRenderer m_sprite;
	Animation& m_anim;
	Physics2D& m_physics;
	AutoControl& m_autoControl;
	
	Direction m_direction;
	float m_speed;

public:
	Item(Object* parent = nullptr);
	~Item();

	void update() override;
	void render() override;
	void setDirection(const Direction& direction);
	virtual void appear();
};