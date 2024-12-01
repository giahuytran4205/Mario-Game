#pragma once
#include "ECS.hpp"
#include "Physics2D.hpp"
#include <functional>
#include <queue>

struct ControlInfo {
	Vector2f pos;
	int duration = 0;
	Vector2f acceleration;
	function<void(int)> action;
	function<bool(int)> condition = nullptr;
};

class AutoControl : public Component {
private:
	Physics2D* m_physics;
	Transform2D* m_transform;
	queue<ControlInfo> m_controlQueue;
	bool m_isControlled;
	ControlInfo m_currentControl;
	int m_countdown;
	int m_elapsedTime;

public:
	AutoControl();
	~AutoControl();

	void init() override;
	void update() override;
	void addMoveByPoint(const Vector2f& pos, int duration, const Vector2f& acceleration, function<void(int)> action = nullptr);
	void addMoveByDistance(const Vector2f& distance, int duration, const Vector2f& acceleration, function<void(int)> action = nullptr);
	void addWaitForMiliseconds(int duration, function<void(int)> action = nullptr);
	void addWaitUntil(function<bool(int)> condition);
	void addAction(function<void()> action);
	bool isControlled();
};