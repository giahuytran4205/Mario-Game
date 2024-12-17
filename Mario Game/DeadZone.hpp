#pragma once
#include "Object.hpp"
#include "Rect.hpp"
#include "Transform2D.hpp"
#include "Collision.hpp"
#include "Mario.hpp"

class DeadZone : public Object {
private:

public:
	DeadZone(Object* parent = nullptr);
	DeadZone(const FRect& rect, Object* parent = nullptr);
	~DeadZone();

	void onCollisionEnter(Collision& col, const Direction& side) override;
};