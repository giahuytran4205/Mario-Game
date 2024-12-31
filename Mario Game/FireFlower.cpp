#include "FireFlower.hpp"
#include "Mario.hpp"

FireFlower::FireFlower(Object* parent) : Item(parent) {
	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_anim.loadFromJsonFile("Resources/Animations/FireFlower.json");
	m_anim.play(0);

	m_sprite.setAnchor(0.5, 0.5);
	m_sprite.setParent(this);
	m_sprite.setRenderOrder(0);

	setRenderOrder(3);

	m_physics.setEnableGravity(false);
	m_physics.setElastic(true);
	getComponent<Collision>().setEnable(false);
}

FireFlower::~FireFlower() {}

void FireFlower::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		Mario& mario = *col.m_entity->convertTo<Mario>();
		if (mario.getAbility() != Mario::INVINCIBLE)
			mario.setAbility(Mario::FIERY);
		destroy();
	}
}

void FireFlower::update() {

}

void FireFlower::appear() {
	m_autoControl.addMoveByDistance(Vector2f(0, -m_transform.height), 1000, Vector2f(0, 0));
	m_autoControl.addAction([&]() {
			m_physics.setBaseVelocity({ 0, 0 });
			m_physics.setEnableGravity(true);

			getComponent<Collision>().setEnable(true);
			getComponent<Collision>().setTrigger(false);
		});
}