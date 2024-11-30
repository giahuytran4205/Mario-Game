#include "Jumper.hpp"
#include "Collision.hpp"
#include "Mario.hpp"
#include "TextureManager.hpp"
#include "GameManager.hpp"
#include <iostream>

Jumper::Jumper(Object* parent) : m_collision(addComponent<Collision>()), m_anim(addComponent<Animation>(m_sprite)) {
	setParent(parent);
	m_transform.setAnchor(0.5, 1);
	FRect rect = m_transform.getRect();
	m_transform.setSize({ 16, 32 });

	m_anim.loadFromJsonFile("Resources/Animations/Jumper.json");
	m_launchTime = m_anim.getTrackLength(0);
	m_cooldown = 0;

	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 1);
}

Jumper::Jumper(const Vector2f pos, Object* parent) : Jumper(parent) {
	m_transform.setPosition(pos);
}

Jumper::Jumper(const Jumper& jumper) : Jumper() {
	m_transform = jumper.m_transform;
	m_anim = jumper.m_anim;
}

Jumper::~Jumper() {}

void Jumper::update() {
	int idx = m_anim.getIndexInCurrentTrack();

	if (m_cooldown > 0) {
		m_anim.play(0);
		m_cooldown -= deltaTime.asMilliseconds();
	}
	else {
		m_anim.stop();
		idx = 0;
	}

	if (idx == 0)
		m_transform.setSize({ 16.0f, 32.0f });
	if (idx == 1)
		m_transform.setSize({ 16.0f, 24.0f });
	if (idx == 2)
		m_transform.setSize({ 16.0f, 16.0f });
	if (idx == 3)
		m_transform.setSize({ 16.0f, 24.0f });
	if (idx == 4)
		m_transform.setSize({ 16.0f, 32.0f });	

}

void Jumper::onCollisionEnter(Collision& col) {
	
}

void Jumper::launch() {
	if (m_cooldown <= 0)
		m_cooldown = m_launchTime;
}

float Jumper::getLauchVelocity() {
	return (m_transform.getSize().y - 32) / 16 * 0.1f - 0.3f;
}