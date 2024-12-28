#include "ItemFireAx.hpp"

ItemAx::ItemAx(Object* parent):
	Enemy(parent, true)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/axe.json");
	m_anim.play(0);
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(2);
	m_transform.setAnchor(0, 0);
	m_physics.setEnableGravity(false);
}

void ItemAx::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isType<Mario>()) {
		hit(true);
	}
}

void ItemAx::hit(bool isDestroy)
{
	if (isDestroy) {
		getComponent<Physics2D>().setStatic(true);
		getComponent<Collision>().setTrigger(true);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
	}
}

void ItemAx::update()
{
}


