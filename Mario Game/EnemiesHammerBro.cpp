#include "EnemiesHammerBro.hpp"
#include "KoopaShell.hpp"
#include "BuzzyShell.hpp"
#include "GameManager.hpp"

// TODO add 2 platform
EnemiesHammerBro::EnemiesHammerBro(Mario& mario, Object* parent) : Enemy(parent), m_mario(mario) {
	m_transform.setSize(16, 32);
	m_transform.setAnchor(0.5, 0.5);

	m_anim.loadFromJsonFile("Resources/Animations/HammerBro.json");
	m_anim.play(State::WALK);
	m_anim.getTrack(State::FIRE).setEnableExitTime(true);
	m_anim.getTrack(State::FIRE).setExitTime(0);
	m_anim.getTrack(State::FIRE).setLoop(false);

	m_direction = Direction::LEFT;

	m_sprite.setParent(this);
	m_sprite.setRenderOrder(3);

	m_physics.setElastic(true);
	m_physics.setEnableGravity(true);

	m_fireCD = 3000;
	m_curFireCD = 0;
	m_speed = 0.02f;
	m_timeChangeDir = 3000;
}

EnemiesHammerBro::EnemiesHammerBro(Mario& mario, const Vector2f& pos, Object* parent) : EnemiesHammerBro(mario, parent) {
	m_transform.setWorldPosition(pos);
}
 
void EnemiesHammerBro::onCollisionEnter(Collision& col, const Direction& side) {
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

//TODO 2 platform
void EnemiesHammerBro::update() {
	float dist = distance(m_mario.getComponent<Transform2D>().getWorldCenter(), m_transform.getWorldCenter());

	if (m_curFireCD > 0)
		m_curFireCD -= deltaTime.asMilliseconds();

	m_anim.play(State::WALK);

	if (m_timeChangeDir > 0)
		m_timeChangeDir -= deltaTime.asMilliseconds();

	if (dist < 120) {
		if (dist > 80)
			fire();

		if (m_mario.getComponent<Transform2D>().getWorldCenter().x < m_transform.getWorldCenter().x)
			m_direction = Direction::LEFT;
		else
			m_direction = Direction::RIGHT;
	}
	else if (m_timeChangeDir <= 0) {
		m_timeChangeDir = 3000;
		m_direction = getOpposite(m_direction);
	}

	if (m_direction == Direction::LEFT) {
		m_sprite.setScale(1, 1);
		m_physics.setBaseVelocityX(-m_speed);
	}
	else if (m_direction == Direction::RIGHT) {
		m_sprite.setScale(-1, 1);
		m_physics.setBaseVelocityX(m_speed);
	}
}

void EnemiesHammerBro::fire() {
	if (m_curFireCD > 0)
		return;

	m_curFireCD = m_fireCD;

	m_anim.play(State::FIRE);
	
	Coroutine fireHammer = spawnHammer();
}

void EnemiesHammerBro::die() {
	destroy();
}

Coroutine EnemiesHammerBro::spawnHammer() {
	co_await WaitForMiliseconds(200);
	Hammer& hammer = Instantiate<Hammer>();

	if (m_direction == Direction::LEFT)
		hammer.getComponent<Transform2D>().setWorldPosition(Vector2f(m_transform.left, m_transform.top) + Vector2f(8, 0));
	else if (m_direction == Direction::RIGHT)
		hammer.getComponent<Transform2D>().setWorldPosition(Vector2f(m_transform.left, m_transform.top) - Vector2f(8, 0));

	hammer.setDestination(m_mario.getComponent<Transform2D>().getWorldCenter());
	co_await WaitForMiliseconds(100);
	hammer.launch();
}