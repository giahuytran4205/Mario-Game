#pragma once
#include "Common.hpp"
#include "Character.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Mario : public Character {
private:
	Physics2D* m_physics2D;
	Collision* m_collision;
	float m_speed;

public:
	Mario();
	~Mario();

	//void init();
	void onCollisionEnter(Collision& col) override;
	void update() override;
};