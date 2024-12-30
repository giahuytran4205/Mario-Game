#pragma once
#include "Enemy.hpp"

class KoopaShell : public Enemy {
private:
	enum State {
		NORMAL,
		MOVE
	};
	State m_state;
	bool m_isLaunch;

public:
	KoopaShell(Object* parent = nullptr);
	~KoopaShell();

	void onCollisionEnter(Collision& col, const Direction& side);
	void update() override;
	void die() override;
};