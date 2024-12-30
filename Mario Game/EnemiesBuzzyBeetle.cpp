#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesGoomba.hpp"
#include "EnemiesKoopaTroopa.hpp"
#include "BuzzyShell.hpp"

EnemiesBuzzyBeetle::EnemiesBuzzyBeetle(Object* parent) : Enemy(parent) {
    m_transform.setSize(16, 16);
    m_transform.setAnchor(0.5, 0.5);
    
	m_anim.loadFromJsonFile("Resources/Animations/BuzzyBeetle.json");
    m_anim.play(0);

    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);

	m_speed = 0.05f;
}

EnemiesBuzzyBeetle::~EnemiesBuzzyBeetle() {
}
void EnemiesBuzzyBeetle::onCollisionEnter(Collision& col, const Direction& side) {
    if (col.m_entity->isType<Fireball>()) {
        destroy();
    }

	if (col.m_entity->isType<Mario>()) {
		if (side == Direction::UP) {
			col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
			die();
		}
		else {
			col.m_entity->convertTo<Mario>()->dead();
		}
	}
	else if (col.m_entity->isDerivedFrom<Block>()) {
		if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_direction = getOpposite(side);
		}
	}
	else if (col.m_entity->isType<EnemiesBuzzyBeetle>()) {
		EnemiesBuzzyBeetle* other = col.m_entity->convertTo<EnemiesBuzzyBeetle>();

		other->m_direction = getOpposite(other->m_direction);
		m_direction = getOpposite(m_direction);
	}
}

void EnemiesBuzzyBeetle::update() {
	if (m_direction == Direction::LEFT) {
		m_sprite.setScale(1, 1);
		m_physics.setBaseVelocityX(-m_speed);
	}
	else if (m_direction == Direction::RIGHT) {
		m_sprite.setScale(-1, 1);
		m_physics.setBaseVelocityX(m_speed);
	}
}

void EnemiesBuzzyBeetle::die() {
	m_isDead = true;
	destroy();
	BuzzyShell& shell = Instantiate<BuzzyShell>();
	shell.setParent(m_parent);
	shell.getComponent<Transform2D>().setCenter(m_transform.getWorldCenter());
}