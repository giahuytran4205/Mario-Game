#include "EnemiesPiranhaPlant.h"

EnemiesPiranhaPlant::EnemiesPiranhaPlant(Mario& mario, Object* parent): 
	Enemy(parent, false), mMario(mario)
{
	m_transform.setSize(16, 24);
	m_anim.loadFromJsonFile("Resources/Animations/pi.json");
	m_anim.play(1);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0.5, 0.5);
	m_physics.setEnableGravity(false);
	m_sprite.setRenderOrder(0);
}

void EnemiesPiranhaPlant::onCollisionEnter(Collision& col, const Direction& side)
{
	    if (col.m_entity->isType<Mario>()) {
			col.m_entity->convertTo<Mario>()->dead();
		// TODO check dead 
    }
	
}

void EnemiesPiranhaPlant::update()
{
	if (m_autoControl.isControlled())
		return;

	const auto posMario = mMario.getPos();
	auto Post = m_transform.getPosition();
	if (posYHide < 0) {
		auto Size = this->getComponent<Transform2D>().getSize().y;
		posYHide = Post.y + Size;
		posYTop = Post.y;
	}

	const auto Distance = std::abs(posMario.x - Post.x);
	const bool isMarioNear = Distance < 50;

	switch (mState) {
	case HIDDEN: {
		if (!isMarioNear) {
			m_autoControl.addMoveByPoint({ Post.x, posYTop }, TIME_RAISING, { 0, 0 }, [&](int time) {});
			mState = SHOW;
		}
		break;
	}
	case SHOW: {

		m_autoControl.addMoveByPoint({ Post.x, posYHide }, TIME_RAISING, { 0, 0 }, [&](int time) {});
		mState = HIDDEN;
		break;
	}

	default:
		break;
	}

}

EnemiesPiranhaPlant::State EnemiesPiranhaPlant::getState()
{
	return mState;
}

void EnemiesPiranhaPlant::setHide(bool isHide)
{
	//std::cout << "Hide: " << isHide << '\n';
	m_sprite.setEnable(!isHide);
	getComponent<Collision>().setTrigger(isHide);
}
