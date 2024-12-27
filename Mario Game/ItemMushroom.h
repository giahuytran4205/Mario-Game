#pragma once
#include "Random.hpp"
#include "Enemy.hpp"
#include "Mario.hpp"
class ItemMushroom : public Enemy
{
	enum State {
		NONE,
		RAISING,
		RUNING,
	};
public:
	enum Type
	{
		GREEN,
		ORANGE,
	};
	static const int TIME_RAISING = 600;
private:
	bool mIsActive{ false };
	State mState{ NONE };
	Vector2f mPosSrc;
	const Type mType;
	float m_speed = -0.05f;
	int m_dir = 1;
	int m_Cnt{ 0 };
public:
	ItemMushroom(Type type,  Object* parent = nullptr);
	~ItemMushroom() = default;
	void setActive(
		const Vector2f& posSrc
	);

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit(bool isDestroy);
	void update();
};

