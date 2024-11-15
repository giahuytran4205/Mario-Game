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
#include <iostream>
using namespace sf;

Mario::Mario() : m_physics2D(addComponent<Physics2D>()), m_collision(addComponent<Collision>()) {
	m_speed = 1.0f;

	Texture* texture = new Texture();
	texture->loadFromFile("Goomba.png");
	m_sprite.setTexture(*texture);

	m_physics2D.setVelocity({ 0, 0 });
	m_physics2D.setGravity(0.05f);

	m_transform.getRect().width = texture->getSize().x;
	m_transform.getRect().height = texture->getSize().y;
	m_transform.setPosition({ 150, 0 });

	m_onJump = false;

	m_anim = &addComponent<Animation>(m_sprite);
	m_anim->loadFromJsonFile("D:/GHuy/OOP/Tile/Mario&Luigi.json");
	
	m_state = State::Normal;

	m_renderOrder = 1;
}

Mario::~Mario() {

}

void Mario::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Block>()) {
		Line line(m_transform.getLastPosition(), m_transform.getPosition());
		gr::Rect rect = col.m_entity->getComponent<Transform2D>().getRect();
		gr::Rect bodyRect = getComponent<Transform2D>().getRect();

		rect = { rect.left - bodyRect.width / 2, rect.top - bodyRect.height / 2, rect.width + bodyRect.width, rect.height + bodyRect.height};
		int side;
		Vector2f pos = line.raycast(rect, side);

		m_transform.adjustPosition(pos);
		m_physics2D.setVelocityY(0);
		m_physics2D.setBaseVelocityY(0);

		if (side == 0 || side == 2) {		// On left side or right side of block
			m_physics2D.setBaseVelocityY(1.0f);
			m_onWall = true;
		}
		else if (side == 1) {				// Above block
			m_onGround = true;
			m_onJump = false;
			m_physics2D.setBaseVelocityY(0);
		}
		else {								// Below block
			m_physics2D.setBaseVelocityY(0.1f);
			col.m_entity->convertTo<Block>()->onHit(false);
		}
	}

	if (col.m_entity->isType<Item>()) {
		col.m_entity->toObject()->destroy();
	}
}

void Mario::update() {
	m_onGround = m_physics2D.getVelocity().y == 0.05f && !m_onJump;
	if (isOnGround()) {
		m_physics2D.setVelocityY(0);
		m_physics2D.setBaseVelocityY(0);
	}

	m_physics2D.setBaseVelocityX(0);
	m_physics2D.setVelocityX(0);

	handleMovement();

	m_anim->play(m_state);
	
	m_onWall = false;

	cout << m_onGround << " " << m_onWall << "\n";
}

void Mario::handleMovement() {
	m_state = State::Normal;

	if (Keyboard::isKeyPressed(Keyboard::A) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(-2.0f);
		}
		else m_physics2D.setBaseVelocityX(-1.0f);

		m_sprite.getSprite().setScale({ -1, 1 });

		m_state = State::Walk;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (isOnGround() || !isOnWall())) {
		if (isOnGround()) {
			m_physics2D.setBaseVelocityX(2.0f);
		}
		else m_physics2D.setBaseVelocityX(1.0f);

		m_sprite.getSprite().setScale({ 1.0f, 1.0f });

		m_state = State::Walk;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		jump();
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_physics2D.setBaseVelocityY(1.0f);
	}

	if (m_onJump) m_state = State::Jump;
}

void Mario::jump(float velY) {
	if (!isOnGround()) return;
	m_onGround = false;
	m_onJump = true;
	m_physics2D.setBaseVelocityY(velY);
	m_state = State::Jump;
}