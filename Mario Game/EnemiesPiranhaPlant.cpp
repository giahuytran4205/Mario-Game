#include "EnemiesPiranhaPlant.hpp"
#include "GameManager.hpp"

EnemiesPiranhaPlant::EnemiesPiranhaPlant(Object* parent) : Enemy(parent) {
	m_transform.setSize(16, 24);
	m_transform.setAnchor(0.5, 0.5);

	m_anim.loadFromJsonFile("Resources/Animations/PiranhaPlant.json");
	m_anim.play(0);

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	m_physics.setEnableGravity(false);

	m_timeAtk = 3000;
	m_atkCD = 2000;
	m_curAtkCD = 0;
}

void EnemiesPiranhaPlant::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Fireball>()) {
		die();
	}

	if (col.m_entity->isType<Mario>()) {
		col.m_entity->convertTo<Mario>()->dead();
    }
}

void EnemiesPiranhaPlant::update() {
	if (m_curAtkCD > 0)
		m_curAtkCD -= deltaTime.asMilliseconds();
	else
		attack();

}

void EnemiesPiranhaPlant::die() {
	m_isDead = true;
	destroy();
}

void EnemiesPiranhaPlant::attack() {
	if (m_curAtkCD > 0)
		return;
	
	m_curAtkCD = m_atkCD;

	m_autoControl.addMoveByDistance(Vector2f(0, -m_transform.height), 1000, Vector2f(0, 0));
	m_autoControl.addWaitForMiliseconds(m_timeAtk);
	m_autoControl.addMoveByDistance(Vector2f(0, m_transform.height), 1000, Vector2f(0, 0));
}