#pragma once
#include "Random.hpp"
#include "Enemy.hpp"
#include "Mario.hpp"
class ItemStar : public Enemy
{

	enum State {
		NONE,
		RAISING,
		RUNING,
	};
	static const int TIME_RAISING = 600;
	static const int TIME_DELAY = 300;
private:
	bool mIsActive{ false };
	State mState{ NONE };
	Vector2f mPosSrc;
	float m_speed = -0.05f;
	float m_speedY = -0.2f;
	int m_dir = 1;
	int m_dirY = 1;
public:
	ItemStar(Object* parent = nullptr);
	~ItemStar() = default;
	void setActive(
		const Vector2f& posSrc
	);
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();

};

