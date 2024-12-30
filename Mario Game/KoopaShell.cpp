#include "KoopaShell.hpp"
#include "GameManager.hpp"
#include "EnemiesKoopaTroopa.hpp"
#include "Mario.hpp"

KoopaShell::KoopaShell(Object* parent) : Enemy(parent) {
	m_physics.setElastic(true);

	m_anim.loadFromJsonFile("Resources/Animations/KoopaShell.json");
	m_anim.play(State::NORMAL);

	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setParent(this);
	m_sprite.setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	setRenderOrder(3);

	m_speed = 0.5f;
	m_isLaunch = false;
	m_state = State::NORMAL;
}

KoopaShell::~KoopaShell() {}

void KoopaShell::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		Mario& mario = *col.m_entity->convertTo<Mario>();

		if (side == Direction::UP) {
			mario.getComponent<Physics2D>().setBaseVelocityY(-0.1f);

			if (!m_isLaunch)
				m_direction = rand(Direction::LEFT, Direction::RIGHT);
			else
				die();
		}
		else if (side == Direction::LEFT || side == Direction::RIGHT) {
			if (!m_isLaunch)
				m_direction = getOpposite(side);
			else
				mario.damaged();
		}

		m_isLaunch = true;
		m_anim.play(State::MOVE);
	}

	if (col.m_entity->isDerivedFrom<Enemy>() && !col.m_entity->isType<KoopaShell>()) {
		col.m_entity->convertTo<Enemy>()->die();
	}

	if (col.m_entity->isType<KoopaShell>()) {
		m_direction = getOpposite(m_direction);
	}

	if (col.m_entity->isType<Fireball>()) {
		die();
	}
}

void KoopaShell::update() {
	if (m_isLaunch) {
		if (m_direction == Direction::LEFT)
			m_physics.setBaseVelocityX(-m_speed);
		else if (m_direction == Direction::RIGHT)
			m_physics.setBaseVelocityX(m_speed);
	}
}

void KoopaShell::die() {
	m_isDead = true;
	destroy();
}