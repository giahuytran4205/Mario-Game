#include "EnemiesHammer.h"

EnemiesHammer::EnemiesHammer(Object* parent) : Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/hammer.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);

	m_physics.setEnableGravity(false);
	setEnable(false);

}

void EnemiesHammer::setActive(const Vector2f& posSrc, const Vector2f& posTarget)
{
	mIsActive = true;
	mPosSrc = posSrc;
	mPosTarget = posTarget;
	m_physics.setEnableGravity(false);
	mState = INIT;

	auto Distance =  posTarget.x - posSrc.x - rand() % 50 - 20;

	mXTagret = posSrc.x + Distance;

	Vector2f dest = { posSrc.x + Distance*0.3f, posSrc.y - 35 };
	m_autoControl.addMoveByPoint(dest, 250, { 0, 0 }, [&](int time) {});
	// show

	setEnable(true);
}


void EnemiesHammer::onCollisionEnter(Collision& col, const Direction& side)
{
}

void EnemiesHammer::hit(bool isDestroy)
{
}

void EnemiesHammer::update()
{
	if (mState == NONE) {
		return;
	}
	if (m_autoControl.isControlled()) {

		return;
	}
	if (mState == INIT) {
		m_autoControl.addMoveByPoint({ mXTagret, 600 }, 800, { 0.000, 0 }, [&](int time) {});
		mState = FALL;
		return;
	}
	if (mState == FALL) {
		// done
		setEnable(false);
		mState = NONE;
		return;
	}

}
