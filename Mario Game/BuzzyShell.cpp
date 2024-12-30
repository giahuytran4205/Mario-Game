#include "BuzzyShell.hpp"
#include "Mario.hpp"
#include "TextureManager.hpp"

BuzzyShell::BuzzyShell(Object* parent) : Enemy(parent) {
	m_physics.setElastic(true);

	setRenderOrder(3);
	
	m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Enemies.png", IntRect(544, 16, 16, 16)));
	m_sprite.setParent(this);
	m_sprite.setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	m_speed = 0.5f;
	m_isLaunch = false;
}

BuzzyShell::~BuzzyShell() {}

void BuzzyShell::onCollisionEnter(Collision& col, const Direction& side) {
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
	}

	if (col.m_entity->isDerivedFrom<Block>()) {
		if (side == Direction::LEFT || side == Direction::RIGHT)
			m_direction = getOpposite(m_direction);
	}

	if (col.m_entity->isDerivedFrom<Enemy>() && !col.m_entity->isType<BuzzyShell>()) {
		col.m_entity->convertTo<Enemy>()->die();
	}

	if (col.m_entity->isType<BuzzyShell>()) {
		m_direction = getOpposite(m_direction);
	}
}

void BuzzyShell::update() {
	if (m_isLaunch) {
		if (m_direction == Direction::LEFT)
			m_physics.setBaseVelocityX(-m_speed);
		else if (m_direction == Direction::RIGHT)
			m_physics.setBaseVelocityX(m_speed);
	}
}

void BuzzyShell::die() {
	m_isDead = true;
	destroy();
}