#pragma once
#include "SFML/Graphics.hpp"
#include "Rect.hpp"
using namespace sf;

class Line {
public:
	float a, b, c;
	Vector2f startPoint, endPoint;
	Line();
	Line(const Vector2f& point1 = {0, 0}, const Vector2f& point2 = {0, 0});
	~Line();

	Vector2f getIntersection(const Line& other);
	void createLine(const Vector2f& point1, const Vector2f& point2);
	float getX(const float& y);
	float getY(const float& x);
	Vector2f raycast(const FRect& rect, int& side);
};

float distance(const Vector2f& point1, const Vector2f& point2);

float cross(const Vector2f& a, const Vector2f& b);

Vector2f normalize(const Vector2f& v);