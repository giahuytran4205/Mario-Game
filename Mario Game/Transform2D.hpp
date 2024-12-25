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
	bool m_firstSetPos;

public:
	Transform2D();
	~Transform2D();

	void init() override;
	Vector2f getPosition();
	Vector2f getLastPosition();
	Vector2f getRotation();
	Vector2f getWorldPosition();
	Vector2f getLastCenter();
	Vector2f getCenter();
	Vector2f getWorldCenter();
	Vector2f transformPoint(const Vector2f& point);
	Vector2f transformPoint(float x, float y);
	Vector2f reverseTransformPoint(const Vector2f& point);
	Vector2f reverseTransformPoint(float x, float y);
	FRect& getRect();
	void update() override;
	void lateUpdate() override;
	void setRect(const FRect& rect);
	void setRect(float left, float top, float width, float height);
	void setPosition(const Vector2f& position);
	void setPosition(float x, float y);
	void setWorldPosition(const Vector2f& position);
	void setWorldPosition(float x, float y);
	void setCenter(const Vector2f& center);
	void setCenter(float x, float y);
	void setRotation(const Vector2f& rotation);
	void setRotation(float angle);
	void move(float dx, float dy);
	void move(const Vector2f& d);
	void adjustPosition(const Vector2f& pos);
	void adjustCenter(const Vector2f& center);
	void adjustCenter(float centerX, float centerY);
	void setParent(Object* parent);

#if DEBUG

private:
	RectangleShape m_shape;
public:
	static VertexArray rectangles;
	void render() override;

#endif // DEBUG

};