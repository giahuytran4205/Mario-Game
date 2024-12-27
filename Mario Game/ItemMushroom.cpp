#include "ItemMushroom.h"

ItemMushroom::ItemMushroom(Type type, Object* parent):
	Enemy(parent, false),
	mType(type)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(5);
	m_transform.setAnchor(0, 0);
	m_physics.setEnableGravity(false);

}

void ItemMushroom::setActive(const Vector2f& posSrc)
{
	mPosSrc = posSrc;
	mState = RAISING;
	mIsActive = true;

	m_autoControl.addMoveByPoint({ posSrc.x, posSrc.y}, TIME_RAISING, { 0, 0 }, [&](int time) {});
}

void ItemMushroom::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		if(m_Cnt > 100){
			//m_sound.play(SoundTrack::STOMP);
			//hit(true);
			//col.m_entity->convertTo<Mario>()->setAbility(Mario::SUPER);
		}


	}
	else if (col.m_entity->isDerivedFrom<Block>()) {
		if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_dir *= -1;
		}
	}
	// TODO

}

void ItemMushroom::hit(bool isDestroy)
{
	if (isDestroy) {
		getComponent<Physics2D>().setStatic(true);
		getComponent<Collision>().setTrigger(true);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
	}
}

void ItemMushroom::update()
{
	
	if (!mIsActive)
		return;
	m_Cnt++;
	if (m_autoControl.isControlled())
		return;

	if (mState == RAISING) {
		mState = RUNING;
		m_collision.setSkipResolveCollide(false);
	}
	else if(mState == RUNING) {
		m_physics.setBaseVelocityX(m_speed * m_dir);
	}
}
