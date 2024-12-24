#pragma once
#include "Common.hpp"
#include "Object.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "Animation.hpp"

class Projectile : public Object {
protected:
	Physics2D& m_physics;
	Animation& m_anim;
	SpriteRenderer m_sprite;
	int m_damage;
	float m_maxDistance;
	float m_speed;
	Vector2f m_direction;
	int m_age;
	
public:
	Projectile(Object* parent = nullptr);
	~Projectile();

	int getDamage() const;
	float getMaxDistance() const;
	int getAge() const;
	Vector2f getDirection() const;
	void setDamage(int damage);
	void setMaxDistance(float maxDistance);
	void setDirection(const Vector2f& direction);
	void update() override;
};