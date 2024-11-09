#pragma once
#include "Rect.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;
const float PI = acos(-1);

class Transform2D : public Component {
private:
	Vector2f m_pos;
	Vector2f m_lastPos;
	Vector2f m_tempPos;
	Vector2f m_rotation;
	Vector2f m_anchor;
	gr::Rect m_rect;
	Object* m_parent;

public:
	Transform2D();
	~Transform2D();

	const Vector2f& getPosition();
	const Vector2f& getLastPosition();
	const Vector2f& getRotation();
	Vector2f getWorldPosition();
	Vector2f transformPoint(const Vector2f& point);
	Vector2f transformPoint(float x, float y);
	Vector2f reverseTransformPoint(const Vector2f& point);
	Vector2f reverseTransformPoint(float x, float y);
	gr::Rect& getRect();
	void setPosition(float x, float y);
	void setPosition(const Vector2f& position);
	void setRotation(const Vector2f& rotation);
	void setRotation(float angle);
	void move(float dx, float dy);
	void move(const Vector2f& d);
	void adjustPosition(const Vector2f& pos);
	void setParent(Object* parent);
	void update() override;
};

Vector2f normalize(const Vector2f& v);