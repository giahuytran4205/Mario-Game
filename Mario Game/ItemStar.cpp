#include "ItemStar.hpp"

ItemStar::ItemStar(Object* parent):
	Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/star.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(2);
	m_transform.setAnchor(0, 0);
	m_physics.setEnableGravity(false);
}

void ItemStar::setActive(const Vector2f& posSrc)
{
	mPosSrc = posSrc;
	mState = RAISING;
	mIsActive = true;

	m_autoControl.addMoveByPoint({ posSrc.x, posSrc.y }, TIME_RAISING, { 0, 0 }, [&](int time) {});
}

void ItemStar::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		m_sound.play(SoundTrack::ONE_UP);
		hit(true);
		col.m_entity->convertTo<Mario>()->setAbility(Mario::INVINCIBLE);
	}
	else if (col.m_entity->isDerivedFrom<Block>()) {
		if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_dir *= -1;
		}
	}
}

void ItemStar::hit(bool isDestroy)
{
	if (isDestroy) {
		getComponent<Physics2D>().setStatic(true);
		getComponent<Collision>().setTrigger(true);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
	}
}

void ItemStar::update()
{
	if (!mIsActive)
		return;
	if (m_autoControl.isControlled())
		return;

	if (mState == RAISING) {
		mState = RUNING;
		m_collision.setSkipResolveCollide(false);
		m_physics.setEnableGravity(true);
		m_autoControl.addWaitForMiliseconds(TIME_DELAY);
	}
	else if (mState == RUNING) {
		m_physics.setBaseVelocityX(m_speed * m_dir);
		m_physics.setBaseVelocityY(m_speedY * m_dirY);
		//m_physics.setAcceleration(Vector2f(0, 0.2 * m_dir));
	}
}
