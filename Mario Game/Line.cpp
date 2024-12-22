#include "Line.hpp"
#include "SFML/Graphics.hpp"
#include "Rect.hpp"
#include <iostream>
using namespace sf;

Line::Line() {

}

Line::Line(const Vector2f& point1, const Vector2f& point2) {
	createLine(point1, point2);
}

Line::~Line() {

}

Vector2f Line::getIntersection(const Line& other) {
	float y = (c * other.a - a * other.c) / (a * other.b - b * other.a);
	float x = getX(y);
	return { x, y };
}

void Line::createLine(const Vector2f& point1, const Vector2f& point2) {
	a = point2.y - point1.y;
	b = point1.x - point2.x;
	c = -a * point1.x - b * point1.y;
	startPoint = point1;
	endPoint = point2;
}

float Line::getX(const float& y) {
	return -c / a - b / a * y;
}

float Line::getY(const float& x) {
	return -c / b - a / b * x;
}

Vector2f Line::raycast(const FRect& rect, Direction& side) {
	if (a == 0 && b == 0) {
		side = Direction::LEFT;
		return startPoint;
	}

	if (a == 0) {
		if (startPoint.x < endPoint.x) side = Direction::LEFT;
		else side = Direction::RIGHT;
		return { side == 0 ? rect.left : rect.right, -c / b };
	}

	if (b == 0) {
		if (startPoint.y < endPoint.y) side = Direction::UP;
		else side = Direction::DOWN;
		return { -c / a, side == 1 ? rect.top : rect.bottom };
	}

	Vector2f points[4];
	points[0] = { rect.left, getY(rect.left) };
	points[1] = { getX(rect.top), rect.top };
	points[2] = { rect.right, getY(rect.right) };
	points[3] = { getX(rect.bottom), rect.bottom };

	float mn = 1e9;

	for (int i = 0; i < 4; i++) {
		if (!rect.pointOverlap(points[i])) continue;
		if (rect.pointOverlap(startPoint)) {
			if (distance(startPoint, points[i]) <= distance(points[i], endPoint)) {
				side = (Direction)i;
			}
		}
		else if (side == -1 || distance(endPoint, points[i]) < mn) {
			mn = distance(startPoint, points[i]);
			side = (Direction)i;
		}
	}
	return points[side];
}

float distance(const Vector2f& point1, const Vector2f& point2) {
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

float cross(const Vector2f& a, const Vector2f& b) {
	return a.x * b.y - a.y * b.x;
}

Vector2f normalize(const Vector2f& v) {
	if (v.x == 0 && v.y == 0)
		return v;

	float magnitude = sqrt(v.x * v.x + v.y * v.y);
	return { v.x / magnitude, v.y / magnitude };
}