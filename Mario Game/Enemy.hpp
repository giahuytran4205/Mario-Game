#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"

class Enemy : public Object {
protected:
	SpriteRenderer m_sprite;
	Animation& m_anim;
	Physics2D& m_physics;

public:
	Enemy(Object* parent = nullptr);
	~Enemy();
};