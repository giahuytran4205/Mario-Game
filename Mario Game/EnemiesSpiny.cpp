#include "EnemiesSpiny.h"

EnemiesSpiny::EnemiesSpiny(Object* parent): Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/Latiku-spawn.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);


	m_physics.setEnableGravity(false);
	m_physics.setElastic(false);
	setEnable(true);
	
}



void EnemiesSpiny::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isType<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            // Đảo ngược hướng di chuyển
            m_physics.setBaseVelocityX(-m_physics.getBaseVelocity().x);
            if (m_physics.getBaseVelocity().x > 0) {
                m_sprite.setScale(-1, 1);
            } else {
                m_sprite.setScale(1, 1);
            }
        }
    } else if (col.m_entity->isType<Mario>()) {
        col.m_entity->convertTo<Mario>()->dead();
    }
}

void EnemiesSpiny::hit(bool isDestroy)
{
	
}

void EnemiesSpiny::update()
{
	if (mState == NONE) {
		return;
	}
	if (m_onWall) {
		m_onWall = false;
		m_physics.setBaseVelocityX(-m_physics.getBaseVelocity().x);
	}
	if (m_autoControl.isControlled()) {

		return;
	}
	if (mState == INIT) {
		m_autoControl.addMoveByPoint({ mPosTarget.x, 430 }, 1000, { 0, 0 }, [&](int time) {});
		mState = EGG;
		return;
	}
	if (mState == NORMAL) {
		// done
		setEnable(false);
		destroy();
		mState = NONE;
		return;
	}
	auto Post = m_transform.getPosition();
	
	if (Post.y >= 430 && mState == EGG) {
		mState = NORMAL;
		m_anim.loadFromJsonFile("Resources/Animations/Latiku-spawn.json");
		m_anim.play(1);
		m_physics.setElastic(true);
		m_collision.setSkipResolveCollide(false);
		m_physics.setAcceleration({ 0,0 });
		m_physics.setEnableGravity(false);
		m_physics.setVelocityY(0);
		m_physics.setVelocityX(mIsRunRight ? 0.05 : -0.05);
		m_autoControl.addWaitForMiliseconds(5000);


	}

	switch (mState)
	{
	case EnemiesSpiny::EGG: {

		break;
	}
	case EnemiesSpiny::NORMAL: {
		
		break;
	}
	default:
		break;
	}


	if (mIsActive) {
		//TODO
	}

}

EnemiesSpiny::State EnemiesSpiny::getState()
{
	return mState;
}

void EnemiesSpiny::setActive(const Vector2f& posSrc, 
	const Vector2f& posTarget, const bool isRunRight)
{
	mIsActive = true;
	mPosSrc = posSrc;
	mPosTarget = posTarget;
	mIsRunRight = isRunRight;
	m_physics.setEnableGravity(false);
	mState = INIT;
	m_anim.loadFromJsonFile("Resources/Animations/Latiku-spawn.json");

	auto Distance =( isRunRight ? 1 : -1 )*abs(posTarget.x - posSrc.x) * 0.4f;
	Vector2f dest = { posSrc.x + Distance , posSrc.y - 50};
	m_autoControl.addMoveByPoint(dest, 800, { 0, 0 }, [&](int time) {});
	// show

}
