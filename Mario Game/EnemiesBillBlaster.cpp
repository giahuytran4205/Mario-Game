#include "EnemiesBillBlaster.hpp"

EnemiesBillBlaster::EnemiesBillBlaster(Mario& mario, Object* parent):
	Enemy(parent, true),
	mMario(mario)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/bill-blaster.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);

	m_physics.setStatic(true);

	m_autoControl.addWaitForMiliseconds(1000);
}

void EnemiesBillBlaster::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		//m_physics.bounce(0);
		m_transform.setPosition(mPos);
	}
}

void EnemiesBillBlaster::hit(bool isDestroy)
{

}

void EnemiesBillBlaster::update()
{

	const auto Pos = m_transform.getPosition();
	if (mPos.x < 0) {
		mPos = Pos;
	}
	m_transform.setPosition(mPos);
	const auto posMario = mMario.getPos();

	const auto Distance = std::abs(Pos.x - posMario.x);


	if (Distance < RANGE_ACTIVE)
	{
		mIsActive = true;
	}
	else
	{
		mIsActive = false;
		return;
	}

	
	mBullet.erase(std::remove_if(begin(mBullet), end(mBullet),
		[](auto bullet)
		{
			return bullet->isActive() == false;
		}),
		end(mBullet));

	if (m_autoControl.isControlled())
		return;	

	auto bullet = new EnemiesBillBlasterBullet(mMario, this->getParent());
	const bool isRight = (Pos.x < posMario.x);
	bullet->getComponent<Transform2D>().setWorldPosition(Pos.x + ((isRight ? 1 : -1) * bullet->getTransform2D().getSize().x),
		/*Pos.y - bullet->getTransform2D().getSize().y/2);*/
		Pos.y);
	bullet->setActive(Pos, isRight);
	mBullet.push_back(bullet);
	m_autoControl.addWaitForMiliseconds(5000);
	

}
