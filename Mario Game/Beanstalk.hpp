#pragma once
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Collision.hpp"

class Beanstalk : public Object {
private:
	SpriteRenderer m_treetop[2];
	SpriteRenderer m_stalk[2];
	float m_growRate;
	bool m_isOnGrowUp;
	bool m_isMature;
	float m_maxHeight;
	Vector2f m_destination;
	int m_destDepth;
	float m_height[2];

public:
	Beanstalk(Object* parent = nullptr);
	Beanstalk(const Vector2f& pos, float maxHeight, const Vector2f& destination, Object* parent = nullptr);
	Beanstalk(const FRect& rect, const Vector2f& destination, Object* parent = nullptr);
	~Beanstalk();

	void update() override;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void setDestDepth(int depth);
	void growUp();
};