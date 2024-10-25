#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Character.hpp"
#include "Collision.hpp"
#include "Physics2D.hpp"
using namespace sf;
using namespace std;

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
	void Update() override;
};