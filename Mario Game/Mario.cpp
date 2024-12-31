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
#include "MapSelectionScene.hpp"
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

	m_backgroundSound.setParent(this);
	m_backgroundSound.addComponent<SoundComponent>().setLoop(true);
	m_backgroundSound.getComponent<SoundComponent>().play(SoundTrack::OVERWORLD);

	m_fireSound.setParent(this);
	m_fireSound.addComponent<SoundComponent>().setLoop(false);

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
	m_lives = 1;
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
		if (col.getCollider().intersects(m_transform) && col.getCollider().bottom <= m_transform.bottom) {
			Portal* portal = col.m_entity->convertTo<Portal>();

			if (Keyboard::isKeyPressed(portal->getEnterKey()) || portal->isAutoEnter()) {
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
			m_autoControl.addMoveByPoint(dest + Vector2f(32, 16), 200, { 0, m_physics2D.getGravity() });
			m_autoControl.addMoveByPoint(Vector2f(m_castleGate.x, dest.y + 16), 1000, { 0, 0 },
				[&](int time) {
					m_direction = Direction::RIGHT;
					m_state = State::WALK; 
				});
			m_autoControl.addAction(
				[&]() {
					m_physics2D.setEnableGravity(true);
					m_collision.setTrigger(false);
					setEnable(false);
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
	
	m_onWall = false;
	m_onJumper = false;
}

void Mario::render() {

}

void Mario::handleMovement() {
	if (m_autoControl.isControlled())
		return;

	m_state = State::NORMAL;

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_physics2D.setBaseVelocityX(-m_speed);

		m_direction = Direction::LEFT;
		m_state = State::WALK;
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
	if (m_ability == Ability::REGULAR || m_ability == Ability::SUPER)
		return;

	if (m_curFireCD > 0)
		return;

	m_curFireCD = m_fireCD;

	m_state = State::FIRE;
	m_anim->getTrack(State::FIRE).setLoop(false);
	m_anim->getTrack(State::FIRE).setEnableExitTime(true);

	Coroutine coroutine = spawnFireball();
}

void Mario::setAbility(Ability ability) {
	m_ability = ability;

	if (ability == Ability::REGULAR) {
		m_anim->loadFromJsonFile("Resources/Animations/Mario&Luigi.json");
		m_transform.setHeight(16);
	}
	else if (ability == Ability::SUPER) {
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
	m_autoControl.addMoveByPoint(m_enteredPortal.getDestination(), 0, { 0, 0 }, [&](int time) {
			GameManager::getInstance()->getView().setCenter(m_transform.getPosition().x, m_enteredPortal.getDestDepth() * 240 + 120);
		});

	if (m_enteredPortal.getOutDirection() != Vector2f(0, 1))
		m_autoControl.addMoveByDistance(m_enteredPortal.getOutDirection() * 16.0f, 1000, { 0, 0 });

	m_autoControl.addAction([&]() {
			m_collision.setTrigger(false);
			m_physics2D.setEnableGravity(true);
			m_sprite.setRenderOrder(3);
			m_onTeleport = false;
		});

	m_sound.play(SoundTrack::WARP);
}

void Mario::onGrabFlagPole() {

}

void Mario::damaged() {
	if (m_ability == Ability::REGULAR)
		dead();
	else if (m_ability == Ability::SUPER || m_ability == Ability::FIERY)
		setAbility(Ability::REGULAR);		
}

void Mario::dead() {
	setAbility(Ability::REGULAR);

	m_isDead = true;
	m_lives--;
	m_state = State::DIE;
	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setBaseVelocityX(0);
	m_physics2D.setBaseVelocityY(-0.2);
	m_collision.setEnable(false);
	m_autoControl.addWaitForMiliseconds(3000);
	m_autoControl.addAction(
		[&]() {
			SceneManager::getInstance()->setCurrentScene<MapSelectionScene>();
		});
	m_sound.play(SoundTrack::DIE);
}

void Mario::revive() {

}

void Mario::win() {
	m_backgroundSound.getComponent<SoundComponent>().stop();
	levelClear();
}

void Mario::levelClear() {
	m_backgroundSound.getComponent<SoundComponent>().play(SoundTrack::LEVEL_CLEAR);
	m_backgroundSound.getComponent<SoundComponent>().setLoop(false);
	Coroutine coroutine = clear();
}

Coroutine Mario::clear() {
	while (m_countdown > 0) {
		m_countdown -= 1000;
		addScore(10);
		co_await WaitForMiliseconds(10);
	}
	launchFirework();
}

void Mario::earnCoins(int coins) {
	m_coins += coins;
}

void Mario::addScore(int score) {
	m_score += score;
}

void Mario::launchFirework() {
	FRect range(m_transform.getWorldPosition().x - 56, m_transform.bottom - 9 * 16, 7 * 16, 4 * 16);
	
	auto coroutine = [](Mario* mario, FRect range) -> Coroutine {
		int numFirework = randRange(5, 10);
		for (int i = 0; i < numFirework; i++) {
			float x = randRange(range.left, range.right);
			float y = randRange(range.top, range.bottom);

			Object& firework = ParticleSystem::getInstance()->addParticle("Resources/Particles/Firework.json", Vector2f(x, y));
			SceneManager::getInstance()->getCurrentScene().getComponent<SoundComponent>().play(SoundTrack::FIREWORK);
			firework.getComponent<Physics2D>().setEnableGravity(false);

			mario->addScore(500);

			co_await WaitForMiliseconds(firework.getComponent<Animation>().getTrackLength(0));
		}
		co_await WaitForMiliseconds(1000);
		SceneManager::getInstance()->setCurrentScene<MapSelectionScene>();
	}(this, range);
}

void Mario::setOutGate(const Vector2f& pos) {
	m_castleGate = pos;
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

Coroutine Mario::spawnFireball() {
	auto spawnFunc = [&]() {
		Fireball* fireball = new Fireball(m_parent);
		if (m_direction == Direction::LEFT) {
			fireball->getComponent<Transform2D>().setWorldPosition(m_transform.left - fireball->getComponent<Transform2D>().width, m_transform.top);
			fireball->setDirection(Vector2f(-1, 0));
		}
		else if (m_direction == Direction::RIGHT) {
			fireball->getComponent<Transform2D>().setWorldPosition(m_transform.right, m_transform.top);
			fireball->setDirection(Vector2f(1, 0));
		}
		m_fireSound.getComponent<SoundComponent>().play(SoundTrack::FIREBALL);
	};

	spawnFunc();
	co_await WaitForMiliseconds(200);
	spawnFunc();
}