#pragma once
#include "Object.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Collision.hpp"
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
	void setTexture(const Texture& texture);
	bool isOnGround();

	//virtual void onCollisionEnter(Collision& col);
	//void render(RenderWindow &window);
};