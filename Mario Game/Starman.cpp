#include "Starman.hpp"
#include "Mario.hpp"

Starman::Starman(Object* parent) : Item(parent) {
	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_anim.loadFromJsonFile("Resources/Animations/Starman.json");
	m_anim.play(0);

	m_sprite.setParent(this);
	m_sprite.setRenderOrder(0);
	m_sprite.setAnchor(0.5, 0.5);

	m_speed = 0.05f;

	setRenderOrder(3);

	m_physics.setEnableGravity(false);
	m_physics.setElastic(true);

	getComponent<Collision>().setEnable(false);
}

Starman::Starman(const Direction& direction, Object* parent) : Starman(parent) {
	m_direction = direction;
}

Starman::~Starman() {}

void Starman::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		col.m_entity->convertTo<Mario>()->setAbility(Mario::INVINCIBLE);
		destroy();
	}
}

void Starman::update() {
	if (!m_autoControl.isControlled()) {
		if (m_direction == Direction::LEFT)
			m_physics.setBaseVelocityX(-m_speed);
		else if (m_direction == Direction::RIGHT)
			m_physics.setBaseVelocityX(m_speed);
	}
}

void Starman::appear() {
	m_autoControl.addMoveByDistance(Vector2f(0, -m_transform.height), 1000, Vector2f(0, 0));
	m_autoControl.addAction([&]() {
			m_physics.setEnableGravity(true);
			m_physics.setBaseVelocityY(-0.2);
			getComponent<Collision>().setEnable(true);
			getComponent<Collision>().setTrigger(false);

			m_sprite.setRenderOrder(3);
		});
}