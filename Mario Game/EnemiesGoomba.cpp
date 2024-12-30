#include "EnemiesGoomba.hpp"
#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesKoopaTroopa.hpp"
#include "KoopaShell.hpp"
#include "BuzzyShell.hpp"
#include "GameScene.hpp"

EnemiesGoomba::EnemiesGoomba(Object* parent) : Enemy(parent) {
    m_transform.setSize(16, 16);
    m_transform.setAnchor(0, 0);

    m_anim.loadFromJsonFile("Resources/Animations/Goomba.json");
	m_anim.play(State::WALK);
    
	m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);

	m_speed = 0.05f;
}

void EnemiesGoomba::onCollisionEnter(Collision& col, const Direction& side) {
    if (col.m_entity->isType<Fireball>()) {
		die();
    }

    if (col.m_entity->isType<Mario>()) {
		Mario& mario = *col.m_entity->convertTo<Mario>();
        Mario::Ability marioAbility = mario.getAbility();

        if (side == Direction::UP) {
			die();
            mario.getComponent<Physics2D>().setBaseVelocityY(-0.1f);
            return;
        }

		if (marioAbility == Mario::REGULAR) {
			mario.damaged();
		}
		else if (marioAbility == Mario::SUPER) {
			mario.setAbility(Mario::REGULAR);
		}
		else if (marioAbility == Mario::FIERY) {
			mario.setAbility(Mario::REGULAR);
		}
		else if (marioAbility == Mario::INVINCIBLE) {
			die();
		}

    }

    if (col.m_entity->isDerivedFrom<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_direction = getOpposite(m_direction);
        }
    }

    if (col.m_entity->isDerivedFrom<Enemy>() && !col.m_entity->isType<BuzzyShell>() && !col.m_entity->isType<KoopaShell>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_direction = getOpposite(m_direction);
        }
    }

	if (col.m_entity->isType<BuzzyShell>() || col.m_entity->isType<KoopaShell>()) {
		die();
	}
}

void EnemiesGoomba::die() {
    m_isDead = true;
	m_anim.play(State::DIE);
	getComponent<Physics2D>().setStatic(true);
	getComponent<Collision>().setTrigger(true);
	getComponent<Collision>().setEnable(false);
	m_autoControl.addWaitForMiliseconds(1000);
	m_autoControl.addAction([&]() { destroy(); });
}

void EnemiesGoomba::update() {
	if (m_direction == Direction::LEFT)
		m_physics.setBaseVelocityX(-m_speed);
	else if (m_direction == Direction::RIGHT)
		m_physics.setBaseVelocityX(m_speed);
}
