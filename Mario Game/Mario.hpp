#pragma once
#include "Common.hpp"
#include "Character.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Mario : public Character {
public:
	enum State {
		Normal,
		Walk,
		Jump,
		Damaged
	};

private:
	Physics2D& m_physics2D;
	Collision& m_collision;
	float m_speed;
	bool m_onJump;
	State m_state;
	Animation* m_anim;

public:
	Mario();
	~Mario();

	//void init();
	void onCollisionEnter(Collision& col) override;
	void update() override;
	void handleMovement();
	void jump(float velY = -3.0f);
};