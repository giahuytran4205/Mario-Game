#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "AutoControl.hpp"

class Enemy : public Object {
protected:
	SpriteRenderer m_sprite;
	Animation& m_anim;
	Physics2D& m_physics;
	AutoControl& m_autoControl;

	Direction m_direction;
	float m_speed;
	bool m_isDead;

public:
	Enemy(Object* parent = nullptr);
	~Enemy();

	virtual void die();
};