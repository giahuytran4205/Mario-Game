#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "SpriteRenderer.hpp"
#include "TextureManager.hpp"
#include "GameManager.hpp"
#include "Mario.hpp"

class Lift : public Object {
private:
	Physics2D& m_physics;
	SpriteRenderer m_sprite;
	Vector2f m_direction;
	float m_speed;
	float m_startOffset;
	float m_endOffset;
	float m_phase;
	bool m_isLaunch;
	Mario* m_mario = nullptr;

public:
	Lift(Object* parent = nullptr);
	Lift(const Vector2f& pos, Object* parent = nullptr);
	Lift(const Vector2f& pos, float length, float startOffset, float endOffset, const Vector2f& direction = { 0, -1 }, float speed = 0, bool isLaunch = false, Object* parent = nullptr);
	~Lift();

	void update() override;
	void onCollisionEnter(Collision& col);
	void setDirection(const Vector2f& direction);
	void setMovementRange(float startOffset, float endOffset);
	void setSpeed(float speed);
	void launch();
	void stop();
};