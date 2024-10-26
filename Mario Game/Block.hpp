#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Collision.hpp"
#include "Physics2D.hpp"
using namespace sf;

class Block : public Object {
private:
	Collision* m_collision;
	Physics2D* m_physics2D;
	int m_id;
public:
	Block(int id);
	~Block();

	void Update() override;
};