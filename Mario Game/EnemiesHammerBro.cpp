#include "EnemiesHammerBro.hpp"
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
}

EnemiesHammerBro::EnemiesHammerBro(Mario& mario, const Vector2f& pos, Object* parent) : EnemiesHammerBro(mario, parent) {
	m_transform.setWorldPosition(pos);
}
 
void EnemiesHammerBro::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		if (side == Direction::UP) {
			col.m_entity->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
			die();
		}
		else {

		}
	}

	if (col.m_entity->isType<Fireball>()) {
		die();
	}
}

void EnemiesHammerBro::hit(bool isDestroy) {

}

//TODO 2 platform
void EnemiesHammerBro::update() {
	float dist = distance(m_mario.getComponent<Transform2D>().getWorldCenter(), m_transform.getWorldCenter());
	float dir = m_mario.getComponent<Transform2D>().getWorldCenter().x - m_transform.getWorldCenter().x;
	
	if (dir != 0)
		dir /= abs(dir);

	m_curFireCD -= deltaTime.asMilliseconds();

	m_anim.play(State::WALK);

	if (dist < 120) {
		if (dist > 50)
			fire();

		m_physics.setBaseVelocityX(m_speed * dir);
	}

	if (dir == -1)
		m_direction = Direction::LEFT;
	else if (dir == 1)
		m_direction = Direction::RIGHT;

	if (m_direction == Direction::LEFT)
		m_sprite.setScale(1, 1);
	else if (m_direction == Direction::RIGHT)
		m_sprite.setScale(-1, 1);
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