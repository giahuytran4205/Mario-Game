#pragma once
#include "Common.hpp"
#include "Object.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Block : public Object {
protected:
	Collision* m_collision;
	Physics2D* m_physics2D;
	int m_id;

public:
	Block();
	Block(Texture& texture, int x = 0, int y = 0);
	Block(Texture& texture, const Vector2f& pos, bool addCollision = false);
	~Block();

	void update() override;
};