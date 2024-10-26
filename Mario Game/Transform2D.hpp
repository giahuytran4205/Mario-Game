#pragma once
#include "Rect.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;
const float PI = acos(-1);

class Transform2D : public Component {
private:
	float m_x;
	float m_y;
	float m_lastX;
	float m_lastY;
	Vector2f m_rotation;
	Vector2f m_anchor;
	gr::Rect m_rect;

public:
	Vector2f getPosition();
	void setPosition(float x, float y);
	void setPosition(const Vector2f& position);
	Vector2f getLastPosition();
	Vector2f getRotation();
	void setRotation(const Vector2f& rotation);
	void setRotation(const float& angle);
	void move(float dx, float dy);
	gr::Rect& getRect();
	void move(Vector2f d);
};

Vector2f normalize(const Vector2f& v);