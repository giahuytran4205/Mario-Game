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
#include <iostream>
using namespace sf;

Mario::Mario() : m_physics2D(addComponent<Physics2D>()), m_collision(addComponent<Collision>()), m_sound(addComponent<SoundComponent>()) {
	m_speed = 0.1f;
	m_jumpSpeed = -0.4f;

	Texture* texture = new Texture();
	texture->loadFromFile("Goomba.png");
	m_sprite.setTexture(*texture);

	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setGravity(0.00625f);

	m_transform.getRect().width = texture->getSize().x;
	m_transform.getRect().height = texture->getSize().y;
	m_transform.setPosition({ 150, 0 });

	m_anim = &addComponent<Animation>(m_sprite);
	m_anim->loadFromJsonFile("Resources/Animations/Mario&Luigi.json");
	
	m_state = State::Normal;

	m_renderOrder = 3;

	m_onEnterPortal = false;
	m_onTeleport = false;
	m_onJump = false;
	m_onJumper = false;

	m_teleportTime = 0;
}

Mario::~Mario() {

}

void Mario::onCollisionEnter(Collision& col) {
	if (isOnTeleport())
		return;

	int side = m_transform.getRect().tangentSide(col.getCollider());

	m_physics2D.setVelocityY(0);
	m_physics2D.setBaseVelocityY(0);

	if (col.m_entity->isType<Block>()) {
		m_onJump = false;
		m_state = State::Normal;

		if (side == 0 || side == 2) {
			m_physics2D.setBaseVelocityY(m_speed);
			m_onWall = true;
		}
		if (side == 3) {
			m_physics2D.setBaseVelocityY(m_speed / 10);
		}
	}

	if (col.m_entity->isType<Jumper>()) {
		m_onJumper = true;
		m_onJump = false;
		m_state = State::Normal;

		Jumper* jumper = col.m_entity->convertTo<Jumper>();

		FRect bodyRect = m_transform.getRect();
		FRect jumperRect = jumper->getComponent<Transform2D>().getRect();

		if (side == 1) {
			jumper->launch();
			m_onJump = false;
			m_jumpSpeed = jumper->getLauchVelocity();
		}
		if (side == 0 || side == 2) {
			m_physics2D.setBaseVelocityY(m_speed);
			m_onWall = true;
		}
		if (side == 3) {
			m_physics2D.setBaseVelocityY(m_speed / 10);
		}
	}

	if (col.m_entity->isType<Item>()) {
		m_sound.play(SoundTrack::COIN);
		col.m_entity->toObject()->destroy();
	}

	if (col.m_entity->isType<Portal>()) {
		if (col.getCollider().contains(m_transform.getPosition() + Vector2f(8, 0))) {
			Portal* portal = col.m_entity->convertTo<Portal>();

			if (Keyboard::isKeyPressed(portal->getEnterKey())) {
				teleport(*portal);
			}
		}
	}
}

void Mario::update() {
	if (isOnTeleport())
		onTeleport();

	handleMovement();

	m_anim->play(m_state);
	
	m_onWall = false;
	m_onJumper = false;
}

void Mario::handleMovement() {
	if (isOnTeleport())
		return;

	if (isOnGround()) {
		m_physics2D.setVelocityY(0);
		m_physics2D.setBaseVelocityY(0);
	}

	m_physics2D.setBaseVelocityX(0);
	m_physics2D.setVelocityX(0);

	m_state = State::Normal;

	if (Keyboard::isKeyPressed(Keyboard::A) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(-2 * m_speed);
		}
		else m_physics2D.setBaseVelocityX(-m_speed);

		m_sprite.getSprite().setScale({ -1, 1 });

		m_state = State::Walk;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(2 * m_speed);
		}
		else m_physics2D.setBaseVelocityX(m_speed);

		m_sprite.getSprite().setScale({ 1, 1 });

		m_state = State::Walk;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_physics2D.setBaseVelocityY(m_speed);
	}

	if (m_onJump) m_state = State::Jump;
}

void Mario::onTeleport() {
	if (m_teleportTime > 0) {
		m_teleportTime -= deltaTime.asMilliseconds();
		m_renderOrder = 1;
	}

	if (m_teleportTime <= 1000 && m_onEnterPortal) {
		m_onEnterPortal = false;
		m_transform.setPosition(m_enteredPortal.getDestination());

		m_physics2D.setBaseVelocity(m_enteredPortal.getOutDirection() * (17.0f / m_teleportTime));
		Vector2f dir = m_enteredPortal.getOutDirection();
		if (m_enteredPortal.getOutDirection() == Vector2f{0, 1}) {
			m_teleportTime = 0;
		}

		GameManager::getInstance()->getView().setCenter(m_transform.getPosition().x, m_enteredPortal.getDestDepth() * 240 + 120);
	}

	if (m_teleportTime <= 0) {
		m_onTeleport = false;
		m_physics2D.setGravity(0.00625f);
		m_physics2D.setBaseVelocity({ 0, 0 });
		m_renderOrder = 3;

	}
}

void Mario::jump(float velY) {
	if (!isOnGround() || isOnWall()) return;

	m_onJump = true;

	if (m_onJumper) {
		m_physics2D.setBaseVelocityY(m_jumpSpeed);
	}
	else m_physics2D.setBaseVelocityY(velY);

	m_state = State::Jump;
	m_sound.play(SoundTrack::BIGJUMP, 100);
}

void Mario::teleport(const Portal& portal) {
	m_enteredPortal = portal;
	m_onTeleport = true;
	m_onEnterPortal = true;
	m_teleportTime = 2000;

	m_physics2D.setGravity(0);
	m_physics2D.setVelocity({ 0, 0 });

	Vector2f dist = m_enteredPortal.getComponent<Transform2D>().getPosition() - m_transform.getPosition() + Vector2f{16, 16};
	Vector2f vel = m_enteredPortal.getInDirection() * 0.001f;
	vel.x *= dist.x;
	vel.y *= dist.y;
	m_physics2D.setBaseVelocity(vel);

	m_sound.play(SoundTrack::WARP);
}

bool Mario::isOnGround() {
	return m_physics2D.getVelocity().y + m_physics2D.getBaseVelocity().y == 0 && !m_onJump;
}

bool Mario::isOnTeleport() {
	return m_onTeleport;
}