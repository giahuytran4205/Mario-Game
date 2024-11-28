#pragma once
#include "Rect.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

const float PI = acos(-1);

class Transform2D : public Component, public FRect {
private:
	Vector2f m_pos;
	Vector2f m_lastPos;
	Vector2f m_rotation;
	Object* m_parent;

public:
	Transform2D();
	~Transform2D();

	Vector2f getPosition();
	Vector2f getLastPosition();
	Vector2f getRotation();
	Vector2f getWorldPosition();
	Vector2f transformPoint(const Vector2f& point);
	Vector2f transformPoint(float x, float y);
	Vector2f reverseTransformPoint(const Vector2f& point);
	Vector2f reverseTransformPoint(float x, float y);
	FRect& getRect();
	void update() override;
	void setPosition(const Vector2f& position);
	void setPosition(float x, float y);
	void setCenter(const Vector2f& center);
	void setCenter(float x, float y);
	void setRotation(const Vector2f& rotation);
	void setRotation(float angle);
	void move(float dx, float dy);
	void move(const Vector2f& d);
	void adjustPosition(const Vector2f& pos);
	void setParent(Object* parent);
};