#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "SoundComponent.hpp"
#include "AutoControl.hpp"

class Enemy : public Object {
protected:
	SpriteRenderer m_sprite;
	Animation& m_anim;
	Physics2D& m_physics;
	AutoControl& m_autoControl;
	SoundComponent& m_sound;
public:
	Enemy(Object* parent = nullptr, const bool isNeedCollision = true);
	~Enemy();
};