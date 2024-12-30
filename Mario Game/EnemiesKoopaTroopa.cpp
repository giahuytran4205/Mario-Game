#include "EnemiesKoopaTroopa.hpp"
#include "KoopaShell.hpp"
#include "BuzzyShell.hpp"

EnemiesKoopaTroopa::EnemiesKoopaTroopa(Object* parent) {
    m_transform.setSize(16, 16);
	m_transform.setAnchor(0.5, 0.5);

    m_anim.loadFromJsonFile("Resources/Animations/KoopaTroopa.json");

    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
}

EnemiesKoopaTroopa::~EnemiesKoopaTroopa() {

}

void EnemiesKoopaTroopa::onCollisionEnter(Collision& col, const Direction& side) {
    if (col.m_entity->isType<Mario>()) {
		Mario& mario = *col.m_entity->convertTo<Mario>();
        if (side == Direction::UP) {
			col.m_entity->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
			die();
        }
		else if (mario.getAbility() == Mario::INVINCIBLE) {
			die();
		}
		else {
			mario.damaged();
		}
    }
    
	if (col.m_entity->isType<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_direction = getOpposite(m_direction);
        }
    }

	if (col.m_entity->isDerivedFrom<Enemy>() && !col.m_entity->isType<BuzzyShell>() && !col.m_entity->isType<KoopaShell>()) {
		if (side == Direction::LEFT || side == Direction::RIGHT)
			m_direction = getOpposite(m_direction);
	}

	if (col.m_entity->isType<BuzzyShell>() || col.m_entity->isType<KoopaShell>()) {
		die();
	}
}

void EnemiesKoopaTroopa::update() {
	if (m_direction == Direction::LEFT) {
		m_sprite.setScale(1, 1);
		m_physics.setBaseVelocityY(-m_speed);
	}
	else if (m_direction == Direction::RIGHT) {
		m_sprite.setScale(-1, 1);
		m_physics.setBaseVelocityY(m_speed);
	}
}

void EnemiesKoopaTroopa::die() {
	m_isDead = true;
	destroy();
	KoopaShell& shell = Instantiate<KoopaShell>();
	shell.setParent(m_parent);
	shell.getComponent<Transform2D>().setCenter(m_transform.getWorldCenter());
}