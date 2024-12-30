#include "MagicMushroom.hpp"
#include "Mario.hpp"
#include "TextureManager.hpp"

MagicMushroom::MagicMushroom(Object* parent) : Item(parent) {
	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setAnchor(0.5, 0.5);
	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(0, 0, 16, 16)));
	m_sprite.setParent(this);
	m_sprite.setRenderOrder(0);

	m_speed = 0.05f;

	setRenderOrder(3);

	m_physics.setEnableGravity(false);
	m_physics.setElastic(true);

	getComponent<Collision>().setEnable(false);
}

MagicMushroom::MagicMushroom(const Direction& direction, Object* parent) : MagicMushroom(parent) {
	m_direction = direction;	
}

MagicMushroom::~MagicMushroom() {}

void MagicMushroom::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		col.m_entity->convertTo<Mario>()->setAbility(Mario::SUPER);
		destroy();
	}
}

void MagicMushroom::update() {
	if (!m_autoControl.isControlled()) {
		if (m_direction == Direction::LEFT)
			m_physics.setBaseVelocityX(-m_speed);
		else if (m_direction == Direction::RIGHT)
			m_physics.setBaseVelocityX(m_speed);
	}
}

void MagicMushroom::appear() {
	m_autoControl.addMoveByDistance(Vector2f(0, -m_transform.height), 1000, Vector2f(0, 0));
	m_autoControl.addAction([&]() {
			m_physics.setEnableGravity(true);
			m_physics.setBaseVelocityY(-0.2);
			getComponent<Collision>().setEnable(true);
			getComponent<Collision>().setTrigger(false);

			m_sprite.setRenderOrder(3);
		});
}