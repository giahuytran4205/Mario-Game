#pragma once
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Collision.hpp"

class Beanstalk : public Object {
private:
	SpriteRenderer m_treetop;
	SpriteRenderer m_stalk;
	float m_growRate;
	bool m_isOnGrowUp;

public:
	Beanstalk(Object* parent = nullptr);
	Beanstalk(const Vector2f& pos, const Vector2f& size, Object* parent = nullptr);
	Beanstalk(const FRect& rect, Object* parent = nullptr);
	~Beanstalk();

	void update() override;
	void onCollisionEnter(Collision& col) override;
	void growUp();
};