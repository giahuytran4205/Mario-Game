#include "Physics2D.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "SFML/Graphics.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"
#include <iostream>

Physics2D::Physics2D() {
	m_static = false;
	m_gravity = 0.00625 / 8;
}

Physics2D::Physics2D(float gravity, bool isStatic) {
	m_gravity = gravity;
	m_static = isStatic;
}

Physics2D::~Physics2D() {}

void Physics2D::init() {
	m_acceleration = { 0, 0 };
	m_transform = &m_entity->getComponent<Transform2D>();
	m_enableGravity = true;
	m_isElastic = false;
}

void Physics2D::update() {
	if (m_static) return;

	Vector2f pos = m_transform->getPosition();
	Vector2f direction = m_transform->getRotation();
	pos += (m_baseVelo + m_velocity) * (float)deltaTime.asMilliseconds();
	m_velocity += m_acceleration * (float)deltaTime.asMilliseconds();

	if (isEnableGravity())
		m_velocity.y += m_gravity * (float)deltaTime.asMilliseconds();

	if (m_isBounce) {
		if (pos.y > m_startPos.y) {
			pos.y = m_startPos.y;
			m_isBounce = false;
			m_velocity.y = 0;
			m_baseVelo.y = 0;
			m_static = true;
		}
	}

	m_transform->setPosition(pos);
}

void Physics2D::lateUpdate() {

}

void Physics2D::render() {

}

bool Physics2D::isStatic() const {
	return m_static;
}

float Physics2D::getMass() {
	return m_mass;
}

void Physics2D::setMass(float mass) {
	m_mass = mass;
}

Vector2f Physics2D::getVelocity() {
	return m_velocity;
}

void Physics2D::setVelocity(const Vector2f& velocity) {
	m_velocity = velocity;
}

Vector2f Physics2D::getBaseVelocity() {
	return m_baseVelo;
}

void Physics2D::setBaseVelocity(const Vector2f& v0) {
	m_baseVelo = v0;
}

void Physics2D::setBaseVelocityX(float v0x) {
	m_baseVelo.x = v0x;
}

void Physics2D::setBaseVelocityY(float v0y) {
	m_baseVelo.y = v0y;
}

void Physics2D::setVelocityX(float velX) {
	m_velocity.x = velX;
}

void Physics2D::setVelocityY(float velY) {
	m_velocity.y = velY;
}

void Physics2D::addVelocity(const Vector2f& v0) {
	m_velocity += v0;
}

Vector2f Physics2D::getAcceleration() {
	return m_acceleration;
}

void Physics2D::setAcceleration(const Vector2f& acceleration) {
	m_acceleration = acceleration;
}

void Physics2D::setGravity(float gravity) {
	m_gravity = gravity;
}

float Physics2D::getGravity() {
	return m_gravity;
}

void Physics2D::setEnableGravity(bool enable) {
	m_enableGravity = enable;
}

bool Physics2D::isEnableGravity() {
	return m_enableGravity;
}

void Physics2D::setStatic(bool isStatic) {
	m_static = isStatic;
}

float Physics2D::getFriction() {
	return m_friction;
}

void Physics2D::setFriction(float friction) {
	m_friction = friction;
}

void Physics2D::bounce(float velY) {
	m_startPos = m_transform->getPosition();
	m_baseVelo.y = velY;
	m_isBounce = true;
	m_static = false;
}

void Physics2D::setElastic(bool isElastic) {
	m_isElastic = isElastic;
}

bool Physics2D::isElastic() {
	return m_isElastic;
}