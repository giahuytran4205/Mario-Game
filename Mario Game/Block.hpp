#pragma once
#include "Common.hpp"
#include "Object.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Block : public Object {
private:
	Collision* m_collision;
	Physics2D* m_physics2D;
	int m_id;
public:
	Block(int id);
	~Block();

	void update() override;
};