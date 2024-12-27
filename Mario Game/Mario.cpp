#include "Mario.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Block.hpp"
#include "GameManager.hpp"
#include "Line.hpp"
#include "Rect.hpp"
#include "Object.hpp"
#include "Physics2D.hpp"
#include "Transform2D.hpp"
#include "Collision.hpp"
#include "Character.hpp"
#include "Item.hpp"
#include "Portal.hpp"
#include "Jumper.hpp"
#include "FlagPole.hpp"
#include "QuestionBlock.hpp"
#include "GameScene.hpp"
#include <iostream>
using namespace sf;

Mario::Mario(Object* parent) : m_autoControl(addComponent<AutoControl>()), m_physics2D(addComponent<Physics2D>()),
							m_collision(addComponent<Collision>()), m_sound(addComponent<SoundComponent>()) 
{
	setParent(parent);
	m_speed = 0.1f;
	m_jumpSpeed = -0.4f;

	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);

	Texture* texture = new Texture();
	texture->loadFromFile("Goomba.png");
	m_sprite.setTexture(*texture);

	m_physics2D.setElastic(true);
	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setGravity(0.00625f / 8);

	m_transform.setSize(16, 16);

	m_anim = &addComponent<Animation>(m_sprite);
	m_anim->loadFromJsonFile("Resources/Animations/Mario&Luigi.json");
	
	m_state = State::NORMAL;

	m_renderOrder = 3;

	m_onEnterPortal = false;
	m_onTeleport = false;
	m_onJump = false;
	m_onJumper = false;
	m_onGrabFlagPole = false;
	m_isDead = false;
	m_isInvincible = false;
	m_fireCD = 1000;
	m_curFireCD = 0;
	m_coins = 0;
	m_score = 0;
	m_lives = 3;
	m_countdown = 400000;
	m_ability = Ability::REGULAR;

	m_teleportTime = 0;

}

Mario::~Mario() {

}

void Mario::onCollisionEnter(Collision& col, const Direction& side) {
	if (side == Direction::DOWN && !col.isTrigger())
		m_onJump = false;

	if (m_autoControl.isControlled())
		return;

	if (col.m_entity->isType<Block>()) {
		m_onJump = false;
		m_state = State::NORMAL;

		if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_onWall = true;
		}
	}

	if (col.m_entity->isType<Jumper>()) {
		m_onJumper = true;
		m_onJump = false;
		m_state = State::NORMAL;

		Jumper* jumper = col.m_entity->convertTo<Jumper>();

		FRect bodyRect = m_transform.getRect();
		FRect jumperRect = jumper->getComponent<Transform2D>().getRect();

		if (side == Direction::UP) {
			m_physics2D.setBaseVelocityY(m_speed / 10);
		}
		if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_physics2D.setBaseVelocityY(m_speed);
			m_onWall = true;
		}
		if (side == Direction::DOWN) {
			jumper->launch();
			m_onJump = false;
			m_jumpSpeed = jumper->getLauchVelocity();
		}
	}

	if (col.m_entity->isType<Item>()) {
		m_sound.play(SoundTrack::COIN);
		col.m_entity->toObject()->destroy();
	}

	if (col.m_entity->isType<Portal>()) {
		if (col.getCollider().contains(m_transform.getPosition())) {
			Portal* portal = col.m_entity->convertTo<Portal>();

			if (Keyboard::isKeyPressed(portal->getEnterKey())) {
				teleport(*portal);
			}
		}
	}

	if (col.m_entity->isType<FlagPole>()) {
		FlagPole* flagPole = col.m_entity->convertTo<FlagPole>();
		
		if (!flagPole->isOnLoweringFlag() && !flagPole->isLoweredFlag()) {
			flagPole->loweringFlag();

			m_physics2D.setEnableGravity(false);
			m_collision.setTrigger(true);

			Vector2f dest(m_transform.getPosition().x, flagPole->getComponent<Transform2D>().getRect().bottom - m_transform.height / 2);

			m_autoControl.addMoveByPoint(dest, 1000, { 0, 0 }, [&](int time) { m_state = State::GRAB_FLAGPOLE; });
			m_autoControl.addWaitUntil([flagPole](int time) { return flagPole->isLoweredFlag(); });
			m_autoControl.addMoveByDistance(Vector2f(16, 0), 0, { 0, 0 }, [&](int time) { m_direction = Direction::LEFT; });
			m_autoControl.addWaitForMiliseconds(500, [&](int time) { m_anim->stop(); });
			m_autoControl.addMoveByPoint(dest + Vector2f(16, 0), 0, { 0, 0 });
			m_autoControl.addMoveByPoint(dest + Vector2f(64, 16), 200, { 0, m_physics2D.getGravity() });
			m_autoControl.addMoveByDistance({ 64, 0 }, 1000, { 0, 0 },
				[&](int time) {
					m_direction = Direction::RIGHT;
					m_state = State::WALK; 
				});
			m_autoControl.addAction(
				[&]() {
					m_physics2D.setEnableGravity(true);
					m_collision.setTrigger(false);
					win();
				});
		}
	}

}

void Mario::update() {
	handleMovement();

	if (!isDead()) {
		if (m_countdown > 0)
			m_countdown -= deltaTime.asMilliseconds();
		else
			dead();
	}

	if (m_direction == Direction::LEFT) {
		m_sprite.setScale(-1, 1);
	}
	else {
		m_sprite.setScale(1, 1);
	}

	m_anim->play(m_state);

	m_curFireCD -= deltaTime.asMilliseconds();
	if (m_curFireCD < 0)
		m_curFireCD = 0;
	

}

void Mario::render() {

}

void Mario::handleMovement() {
	if (m_autoControl.isControlled())
		return;

	/*if (isOnGround()) {
		m_physics2D.setVelocityY(0);
		m_physics2D.setBaseVelocityY(0);
	}*/

	m_state = State::NORMAL;

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_physics2D.setBaseVelocityX(-m_speed);

		m_direction = Direction::LEFT;
		m_state = State::WALK;
	}
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		Vector2f pos = m_transform.getWorldPosition();
		std::cout << "Mario position - X: " << pos.x << " Y: " << pos.y << "\n";
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		m_physics2D.setBaseVelocityX(m_speed);

		m_direction = Direction::RIGHT;
		m_state = State::WALK;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_physics2D.setBaseVelocityY(m_speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::G)) {
		setAbility(Ability::FIERY);
	}

	if (Keyboard::isKeyPressed(Keyboard::I)) {
		setAbility(Ability::SUPER);
	}
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		setAbility(Ability::INVINCIBLE);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		fire();
	}

	if (m_onJump) m_state = State::JUMP;
}

void Mario::jump(float velY) {
	if (!isOnGround() || isOnWall()) return;
	m_onJump = true;

	if (m_onJumper) {
		m_physics2D.setBaseVelocityY(m_jumpSpeed);
	}
	else m_physics2D.setBaseVelocityY(velY);

	m_state = State::JUMP;
	m_sound.play(SoundTrack::BIGJUMP, 100);
}

void Mario::fire() {
	if (m_curFireCD > 0)
		return;

	m_curFireCD = m_fireCD;

	m_state = State::FIRE;
	m_anim->getTrack(State::FIRE).setLoop(false);
	m_anim->getTrack(State::FIRE).setEnableExitTime(true);

	Coroutine coroutine = [](Mario* mario) -> Coroutine {
		Fireball* fireball = new Fireball(mario->m_parent);
		if (mario->m_direction == Direction::LEFT) {
			fireball->getComponent<Transform2D>().setWorldPosition(mario->m_transform.left - fireball->getComponent<Transform2D>().width, mario->m_transform.top);
			fireball->setDirection(Vector2f(-1, 0));
		}
		else if (mario->m_direction == Direction::RIGHT) {
			fireball->getComponent<Transform2D>().setWorldPosition(mario->m_transform.right, mario->m_transform.top);
			fireball->setDirection(Vector2f(1, 0));
		}
		
		co_await WaitForMiliseconds(200);

		Fireball* fireball2 = new Fireball(mario->m_parent);
		if (mario->m_direction == Direction::LEFT) {
			fireball2->getComponent<Transform2D>().setWorldPosition(mario->m_transform.left - fireball2->getComponent<Transform2D>().width, mario->m_transform.top);
			fireball2->setDirection(Vector2f(-1, 0));
		}
		else if (mario->m_direction == Direction::RIGHT) {
			fireball2->getComponent<Transform2D>().setWorldPosition(mario->m_transform.right, mario->m_transform.top);
			fireball2->setDirection(Vector2f(1, 0));
		}
	}(this);
}

void Mario::setAbility(Ability ability) {
	m_ability = ability;

	if (ability == Ability::SUPER) {
		m_anim->loadFromJsonFile("Resources/Animations/BigMario.json");
		m_transform.setHeight(32);
	}
	else if (ability == Ability::FIERY) {
		m_anim->loadFromJsonFile("Resources/Animations/FieryMario.json");
		m_transform.setHeight(32);
	}
	else if (ability == Ability::INVINCIBLE) {
		m_anim->loadFromJsonFile("Resources/Animations/InvincibleMario.json");
		m_transform.setHeight(32);
	}
}

void Mario::teleport(const Portal& portal) {
	if (m_onTeleport) return;

	m_enteredPortal = portal;
	m_onTeleport = true;
	m_onEnterPortal = true;
	m_teleportTime = 2000;

	m_physics2D.setEnableGravity(false);
	m_physics2D.setVelocity({ 0, 0 });

	m_collision.setTrigger(true);
	m_sprite.setRenderOrder(1);

	Vector2f dist = m_enteredPortal.getComponent<Transform2D>().getCenter() - m_transform.getPosition() + Vector2f(16, 16);
	dist.x *= m_enteredPortal.getInDirection().x;
	dist.y *= m_enteredPortal.getInDirection().y;

	m_autoControl.addMoveByDistance(dist, 1000, {0, 0});
	m_autoControl.addMoveByPoint(m_enteredPortal.getDestination(), 0, { 0, 0 },
		[&](int time) {
			m_collision.setTrigger(false);
			m_physics2D.setEnableGravity(true);
			m_sprite.setRenderOrder(3);
			GameManager::getInstance()->getView().setCenter(m_transform.getPosition().x, m_enteredPortal.getDestDepth() * 240 + 120);
			m_onTeleport = false;
		});

	m_sound.play(SoundTrack::WARP);
}

void Mario::onGrabFlagPole() {

}

void Mario::dead() {
	if (m_lives == 0) {
		// Game over
	}

	m_isDead = true;
	m_lives--;
	m_state = State::DIE;
	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setBaseVelocityX(0);
	m_physics2D.setBaseVelocityY(-0.2);
	m_autoControl.addWaitForMiliseconds(3000);
	m_sound.play(SoundTrack::DIE);
}

void Mario::win() {
	
}

void Mario::earnCoins(int coins) {
	m_coins += coins;
}

void Mario::addScore(int score) {
	m_score += score;
}

bool Mario::isOnGround() const {
	return m_physics2D.getVelocity().y + m_physics2D.getBaseVelocity().y == 0 && !m_onJump;
}

bool Mario::isOnTeleport() const {
	return m_onTeleport;
}

bool Mario::isOnGrabFlagPole() const {
	return m_onGrabFlagPole;
}

bool Mario::isDead() const {
	return m_isDead;
}

int Mario::getLives() const {
	return m_lives;
}

int Mario::getCoins() const {
	return m_coins;
}

int Mario::getScore() const {
	return m_score;
}

Time Mario::getCountdownTime() const {
	return milliseconds(m_countdown);
}

Mario::Ability Mario::getAbility() const {
	return m_ability;
}

Vector2f Mario::getPos()
{
	//m_collision.getTangentPoint().x
	//m_entity->
	//Transform2D tf1 = col->m_entity->getComponent<Transform2D>();
	return m_physics2D.m_entity->getComponent<Transform2D>().getPosition();
}
