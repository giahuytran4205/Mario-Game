#include "ItemFireFlower.hpp"

ItemFireFlower::ItemFireFlower(Object* parent):
	Enemy(parent, false)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/flower.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(2);
	m_transform.setAnchor(0, 0);
	m_physics.setEnableGravity(false);
}

void ItemFireFlower::setActive(const Vector2f& posSrc)
{
	mPosSrc = posSrc;
	mIsActive = true;
	m_autoControl.addMoveByPoint({ posSrc.x, posSrc.y }, TIME_RAISING, { 0, 0 }, [&](int time) {});
}

void ItemFireFlower::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		//m_sound.play(SoundTrack::STOMP);
		hit(true);
		col.m_entity->convertTo<Mario>()->setAbility(Mario::FIERY);
	}
}

void ItemFireFlower::hit(bool isDestroy)
{
	if (isDestroy) {
		getComponent<Physics2D>().setStatic(true);
		getComponent<Collision>().setTrigger(true);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
	}
}

void ItemFireFlower::update()
{
	if (!mIsActive)
		return;
	if (m_autoControl.isControlled())
		return;

	m_collision.setSkipResolveCollide(false);
	m_physics.setEnableGravity(true);

}


