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
#include <iostream>
using namespace sf;

Mario::Mario() {
	m_speed = 1.0f;

	Texture* texture = new Texture();
	texture->loadFromFile("Goomba.png");
	m_sprite.setTexture(*texture);

	m_physics2D = &addComponent<Physics2D>();
	m_collision = &addComponent<Collision>();

	m_physics2D->setVelocity({ 0, 0 });
	m_physics2D->setGravity(0.05f);

	m_transform.getRect().width = texture->getSize().x;
	m_transform.getRect().height = texture->getSize().y;
	m_transform.setPosition({ 50, 0 });
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

		m_transform.setPosition(pos);
		m_physics2D->setVelocityY(0);
		m_physics2D->setBaseVelocityY(0);

		if (side == 0 || side == 2) {		// On left side or right side of block
			//m_physics2D->setBaseVelocityY(1.0f);
			m_physics2D->setBaseVelocityX(0);
			m_physics2D->setVelocityX(0);
			//if (!isOnGround()) m_transform.move({ 0, 0.5f });
			//m_onGround = true;
		}
		else if (side == 1) {				// Above block
			m_onGround = true;
			m_physics2D->setBaseVelocityY(0);
		}
		else {								// Below block
			m_physics2D->setBaseVelocityY(1.0f);
		}
	}
}

void Mario::update() {
	//m_physics2D->setBaseVelocityX(m_transform.getRotation().x * m_speed);
	m_transform.setRotation({ 0, 0 });
	m_physics2D->setBaseVelocityX(0);

	if (isOnGround()) m_physics2D->setVelocityY(0);
	
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		m_physics2D->setBaseVelocityX(-1.5f);
		//m_transform.move({ -1.0f, 0 });
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		m_physics2D->setBaseVelocityX(1.5f);
		//m_transform.move({ 1.0f, 0 });
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (isOnGround()) {
			m_physics2D->setBaseVelocityY(-3.0f);
			m_onGround = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		m_physics2D->setBaseVelocityY(3.0f);
	}
	m_onGround = false;
}