#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "SingleBalanceLift.hpp"

class BalanceLifts : public Object {
private:
	SingleBalanceLift m_lifts[2];
	SpriteRenderer m_pivot[2];
	SpriteRenderer m_cable[3];

public:
	BalanceLifts(Object* parent = nullptr);
	BalanceLifts(const Vector2f& firstLiftPos, const Vector2f& secondLiftPos, float pivotY, float amplitude = 25.0f, float speed = 0.001f);
	~BalanceLifts();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void setAmplitude(float amplitude);
	void setSpeed(float speed);
};