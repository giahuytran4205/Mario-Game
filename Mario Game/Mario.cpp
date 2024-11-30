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
#include <iostream>
using namespace sf;

Mario::Mario(Object* parent) : m_physics2D(addComponent<Physics2D>()), m_collision(addComponent<Collision>()),
				 m_sound(addComponent<SoundComponent>()), m_autoControl(addComponent<AutoControl>())
{
	setParent(parent);
	m_speed = 0.1f;
	m_jumpSpeed = -0.4f;

	m_transform.setAnchor(0.5, 0.5);

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);

	Texture* texture = new Texture();
	texture->loadFromFile("Goomba.png");
	m_sprite.setTexture(*texture);

	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setGravity(0.00625f / 8);

	m_transform.setSize(16, 16);
	m_transform.setPosition(150, 0);

	m_anim = &addComponent<Animation>(m_sprite);
	m_anim->loadFromJsonFile("Resources/Animations/Mario&Luigi.json");
	
	m_state = State::NORMAL;

	m_renderOrder = 3;

	m_onEnterPortal = false;
	m_onTeleport = false;
	m_onJump = false;
	m_onJumper = false;
	m_onGrabFlagPole = false;

	m_teleportTime = 0;
}

Mario::~Mario() {

}

void Mario::onCollisionEnter(Collision& col) {
	int side = m_transform.getRect().tangentSide(col.getCollider());

	if (m_autoControl.isControlled())
		return;

	if (col.m_entity->isType<Block>()) {
		m_onJump = false;
		m_state = State::NORMAL;

		if (side == 1) {
			m_physics2D.setBaseVelocityY(m_speed / 10);
		}
		if (side == 0 || side == 2) {
			m_physics2D.setBaseVelocityY(m_speed);
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

		if (side == 1) {
			m_physics2D.setBaseVelocityY(m_speed / 10);
		}
		if (side == 0 || side == 2) {
			m_physics2D.setBaseVelocityY(m_speed);
			m_onWall = true;
		}
		if (side == 3) {
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

			Vector2f dest(m_transform.getPosition().x, flagPole->getComponent<Transform2D>().getRect().bottom - 16);

			m_autoControl.addMoveByPoint(dest, 1000, { 0, 0 }, [&](int time) { m_state = State::GRAB_FLAGPOLE; });
			m_autoControl.addWaitUntil([flagPole](int time) { return flagPole->isLoweredFlag(); });
			m_autoControl.addMoveByDistance(Vector2f(16, 0), 0, { 0, 0 }, [&](int time) { m_direction = Direction::LEFT; });
			m_autoControl.addWaitForMiliseconds(500, [&](int time) { m_anim->stop(); });
			m_autoControl.addMoveByPoint(dest + Vector2f(16, 0), 0, { 0, 0 });
			m_autoControl.addMoveByPoint(dest + Vector2f(64, 24), 200, { 0, m_physics2D.getGravity() });
			m_autoControl.addMoveByDistance({ 128, 0 }, 1000, { 0, 0 },
				[&](int time) {
					m_direction = Direction::RIGHT;
					m_state = State::WALK; 
				});
		}
	}

}

void Mario::update() {
	handleMovement();

	if (m_direction == Direction::LEFT) {
		m_sprite.setScale(-1, 1);
	}
	else {
		m_sprite.setScale(1, 1);
	}

	m_anim->play(m_state);
	
	m_onWall = false;
	m_onJumper = false;
}

void Mario::render() {

}

void Mario::handleMovement() {
	if (m_autoControl.isControlled())
		return;

	if (isOnGround()) {
		m_physics2D.setVelocityY(0);
		m_physics2D.setBaseVelocityY(0);
	}

	m_physics2D.setBaseVelocityX(0);
	m_physics2D.setVelocityX(0);

	m_state = State::NORMAL;

	if (Keyboard::isKeyPressed(Keyboard::A) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(-2 * m_speed);
		}
		else m_physics2D.setBaseVelocityX(-m_speed);

		m_direction = Direction::LEFT;
		m_state = State::WALK;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(2 * m_speed);
		}
		else m_physics2D.setBaseVelocityX(m_speed);

		m_direction = Direction::RIGHT;
		m_state = State::WALK;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_physics2D.setBaseVelocityY(m_speed);
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

void Mario::teleport(const Portal& portal) {
	if (m_onTeleport) return;

	m_enteredPortal = portal;
	m_onTeleport = true;
	m_onEnterPortal = true;
	m_teleportTime = 2000;

	m_physics2D.setEnableGravity(false);
	m_physics2D.setVelocity({ 0, 0 });

	m_collision.setTrigger(true);
	m_renderOrder = 1;

	Vector2f dist = m_enteredPortal.getComponent<Transform2D>().getCenter() - m_transform.getPosition() + Vector2f(16, 16);
	dist.x *= m_enteredPortal.getInDirection().x;
	dist.y *= m_enteredPortal.getInDirection().y;

	m_autoControl.addMoveByDistance(dist, 1000, {0, 0});
	m_autoControl.addMoveByPoint(m_enteredPortal.getDestination(), 0, { 0, 0 },
		[&](int time) {
			m_collision.setTrigger(false);
			m_physics2D.setEnableGravity(true);
			m_renderOrder = 3;
			GameManager::getInstance()->getView().setCenter(m_transform.getPosition().x, m_enteredPortal.getDestDepth() * 240 + 120);
			m_onTeleport = false;
		});

	m_sound.play(SoundTrack::WARP);
}

void Mario::onGrabFlagPole() {

}

bool Mario::isOnGround() {
	return m_physics2D.getVelocity().y + m_physics2D.getBaseVelocity().y == 0 && !m_onJump;
}

bool Mario::isOnTeleport() {
	return m_onTeleport;
}

bool Mario::isOnGrabFlagPole() {
	return m_onGrabFlagPole;
}