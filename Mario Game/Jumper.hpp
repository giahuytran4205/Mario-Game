#pragma once
#include "Object.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Animation.hpp"

class Jumper : public Object {
private:
	Collision& m_collision;
	Animation& m_anim;
	int m_launchTime;
	int m_cooldown;

public:
	Jumper();
	Jumper(const Vector2f pos);
	Jumper(const Jumper& jumper);
	~Jumper();

	void update() override;
	void onCollisionEnter(Collision& col) override;
	void launch();
	float getLauchVelocity();
};