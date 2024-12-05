#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "Lift.hpp"

class SingleBalanceLift : public Lift {
private:
	SingleBalanceLift* m_otherLift;
	Mario* m_mario = nullptr;
	Vector2f m_balancePos;
	float m_phase;
	float m_amplitude;

public:
	SingleBalanceLift(Object* parent = nullptr);
	SingleBalanceLift(const Vector2f& pos, float amplitude = 25.0f, float speed = 0.001f);
	~SingleBalanceLift();

	void update() override;
	void onCollisionEnter(Collision& col) override;
	void setAmplitude(float amplitude);
	void linkOtherLift(SingleBalanceLift* other);
};