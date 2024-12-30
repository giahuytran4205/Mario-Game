#pragma once
#include "ECS.hpp"
#include "SpecialObject.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"
#include "SpriteRenderer.hpp"
#include "TextureManager.hpp"
#include "GameManager.hpp"
#include "Mario.hpp"

class Lift : public SpecialObject {
protected:
	Physics2D& m_physics;
	SpriteRenderer m_sprite;
	Direction m_direction;
	float m_speed;
	float m_startOffset;
	float m_endOffset;
	float m_phase;
	bool m_isCircular;
	bool m_isLoop;
	bool m_isLaunch;
	bool m_finish;
	Mario* m_mario = nullptr;

public:
	Lift(Object* parent = nullptr);
	Lift(const Vector2f& pos, Object* parent = nullptr);
	Lift(const Vector2f& pos, float startOffset, float endOffset, Direction direction = DOWN, bool isLaunch = false, float length = 48, float speed = 0.001f, Object* parent = nullptr);
	~Lift();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void setDirection(Direction direction);
	void setMovementRange(float startOffset, float endOffset);
	void setSpeed(float speed);
	void setCircular(bool isCircular);
	void setLoop(bool isLoop);
	void launch();
	void stop();
};