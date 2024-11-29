#pragma once
#include "ECS.hpp"
#include "Physics2D.hpp"
#include <queue>

struct ControlInfo {
	Vector2f pos;
	int duration = 0;
	Vector2f acceleration;
};

class AutoControl : public Component {
private:
	Physics2D* m_physics;
	Transform2D* m_transform;
	queue<ControlInfo> m_controlQueue;
	bool m_isControlled;
	float m_countdown;

public:
	AutoControl();
	~AutoControl();

	void init() override;
	void update() override;
	void addControl(const Vector2f& pos, int duration, const Vector2f& acceleration);
	bool isControlled();
};