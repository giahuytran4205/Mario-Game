#pragma once
#include "SFML/Graphics.hpp"
#include "Common.hpp"
#include "Object.hpp"
#include "Animation.hpp"
using namespace sf;

class Character : public Object {
protected:
	enum Direction {
		LEFT,
		RIGHT
	};

	SpriteRenderer m_sprite;
	int m_maxHealth;
	int m_health;
	Direction m_direction;
	bool m_onGround;
	bool m_onWall;

public:
	Character();
	~Character();

	int getMaxHealth();
	void setMaxHealth(int maxHealth);
	int getHealth();
	void setHealth(int health);
	void setTexture(Texture& texture);
	bool isOnGround();
	bool isOnWall();

	//virtual void onCollisionEnter(Collision& col);
	//void render(RenderWindow &window);
};