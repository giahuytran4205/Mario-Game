#pragma once
#include "Common.hpp"
#include "Character.hpp"
#include "SFML/Graphics.hpp"
#include "SoundComponent.hpp"
#include "Portal.hpp"
#include "AutoControl.hpp"
#include "Random.hpp"
#include "Coroutine.hpp"
#include "Fireball.hpp"
#include "CheepCheepNormal.hpp"
using namespace sf;

class Mario : public Character {
public:
	enum State {
		NORMAL,
		WALK,
		JUMP,
		GRAB_FLAGPOLE,
		DIE,
		DUCK,
		FIRE,
		DAMAGED,
	};

	enum Ability {
		REGULAR,
		SUPER,
		FIERY,
		INVINCIBLE
	};

private:
	Physics2D& m_physics2D;
	Collision& m_collision;
	SoundComponent& m_sound;
	AutoControl& m_autoControl;
	Animation* m_anim;
	State m_state;
	Ability m_ability;
	float m_speed;
	float m_jumpSpeed;
	bool m_isAutoControlled;
	bool m_onJump;
	bool m_onEnterPortal;
	bool m_onTeleport;
	bool m_onJumper;
	bool m_onGrabFlagPole;
	bool m_isDead;
	bool m_isInvincible;
	int m_teleportTime;
	float m_fireCD;
	float m_curFireCD;
	Portal m_enteredPortal;

	int m_lives;
	int m_coins;
	int m_score;
	float m_countdown;

	friend class EnemiesCheepCheepNormal;

public:
	Mario(Object* parent = nullptr);
	~Mario();

	//void init();
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update() override;
	void render() override;
	void onTeleport();
	void handleMovement();
	void jump(float velY = -0.35f);
	void fire();
	void setAbility(Ability ability);
	void teleport(const Portal& portal);
	void onGrabFlagPole();
	void dead();
	void win();
	void earnCoins(int coins);
	void addScore(int score);
	bool isOnGround() const;
	bool isOnTeleport() const;
	bool isOnGrabFlagPole() const;
	bool isDead() const;
	int getLives() const;
	int getCoins() const;
	int getScore() const;
	Time getCountdownTime() const;
	Ability getAbility() const;
	Vector2f getPos();
};