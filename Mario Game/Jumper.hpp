#pragma once
#include "SpecialObject.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Animation.hpp"

class Jumper : public SpecialObject {
private:
	SpriteRenderer m_sprite;
	Collision& m_collision;
	Animation& m_anim;
	int m_launchTime;
	int m_cooldown;

public:
	Jumper(Object* parent = nullptr);
	Jumper(const Vector2f pos, Object* parent = nullptr);
	Jumper(const Jumper& jumper);
	~Jumper();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void launch();
	float getLauchVelocity();
};