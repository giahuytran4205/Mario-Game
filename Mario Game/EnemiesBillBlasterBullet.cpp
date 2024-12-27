#include "EnemiesBillBlasterBullet.hpp"

EnemiesBillBlasterBullet::EnemiesBillBlasterBullet(Mario& mario, Object* parent):
	mMario(mario), Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/billblasterbullet.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);

	m_physics.setEnableGravity(false);
	m_physics.setElastic(false);
	setEnable(true);


}

void EnemiesBillBlasterBullet::setActive(const Vector2f& posSrc,
	const bool isRunRight)
{
	std::cout << "setActive" << std::endl;
	mIsActive = true;
	mPosSrc = posSrc;
	m_physics.setBaseVelocityX(isRunRight ? mSpeed :-mSpeed);
	m_autoControl.addWaitForMiliseconds(10000);

}

void EnemiesBillBlasterBullet::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		if (side == Direction::UP) {
		
		}
		else {
			col.m_entity->convertTo<Mario>()->dead();
		}

	}
}

void EnemiesBillBlasterBullet::hit(bool isDestroy)
{
}

void EnemiesBillBlasterBullet::update()
{
	if(!mIsActive)
		return;

	// check pos mario
	const auto posMario = mMario.getPos();


	//
	if(m_autoControl.isControlled())
		return;
	else
	{
		mIsActive = false;
		destroy();
	}
}
