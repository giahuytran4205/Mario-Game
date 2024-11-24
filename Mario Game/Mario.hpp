#pragma once
#include "Common.hpp"
#include "Character.hpp"
#include "SFML/Graphics.hpp"
#include "SoundComponent.hpp"
#include "Portal.hpp"
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
	SoundComponent& m_sound;
	Animation* m_anim;
	State m_state;
	float m_speed;
	float m_jumpSpeed;
	bool m_onJump;
	bool m_onEnterPortal;
	bool m_onTeleport;
	bool m_onJumper;
	int m_teleportTime;
	Portal m_enteredPortal;

public:
	Mario();
	~Mario();

	//void init();
	void onCollisionEnter(Collision& col) override;
	void update() override;
	void onTeleport();
	void handleMovement();
	void jump(float velY = -0.35f);
	void teleport(const Portal& portal);
	bool isOnGround();
	bool isOnTeleport();
};