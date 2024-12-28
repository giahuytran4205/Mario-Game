#include "EnemiesBillBlasterBullet.hpp"

EnemiesBillBlasterBullet::EnemiesBillBlasterBullet(Mario& mario, Object* parent):
	mMario(mario), Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/BillBlasterBullet.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);

	m_physics.setEnableGravity(false);
	m_physics.setElastic(false);
	setEnable(true);
	m_isDead = false;

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
			m_sound.play(SoundTrack::STOMP);
			hit(true);
			col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
			destroy();
		}
		else {
			col.m_entity->convertTo<Mario>()->dead();
		}

	}
	if (col.m_entity->isDerivedFrom<Projectile>()) {
		destroy();
	}
}

void EnemiesBillBlasterBullet::hit(bool isDestroy)
{
	if (isDestroy) {
		m_isDead = true;
		m_anim.play(0);
		getComponent<Physics2D>().setStatic(true);
		getComponent<Collision>().setTrigger(true);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
	}
}

void EnemiesBillBlasterBullet::update()
{

	if (m_isDead)
		return;
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
