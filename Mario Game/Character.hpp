#pragma once
#include "SFML/Graphics.hpp"
#include "Common.hpp"
#include "Object.hpp"
using namespace sf;

class Character : public Object {
protected:
	int m_maxHealth;
	int m_health;
	bool m_onGround;
	Collision* m_collision;

public:
	Character();
	~Character();

	int getMaxHealth();
	void setMaxHealth(int maxHealth);
	int getHealth();
	void setHealth(int health);
	void setTexture(Texture& texture);
	bool isOnGround();

	//virtual void onCollisionEnter(Collision& col);
	//void render(RenderWindow &window);
};