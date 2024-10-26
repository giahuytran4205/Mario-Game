#include "Physics2D.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "SFML/Graphics.hpp"
#include "Transform2D.hpp"

void Physics2D::init() {
	m_static = false;
	m_gravity = 0;
	m_acceleration = { 0, 0 };
}

void Physics2D::update() {
	if (m_static) return;
	Vector2f pos = m_entity->getComponent<Transform2D>().getPosition();
	Vector2f direction = m_entity->getComponent<Transform2D>().getRotation();
	pos += m_baseVelo + m_velocity;
	m_velocity += m_acceleration;
	m_velocity.y += m_gravity;
	m_entity->getComponent<Transform2D>().setPosition(pos);
}

void Physics2D::lateUpdate() {
	/*if (m_static) return;
	Vector2f pos = m_entity->getComponent<Transform2D>().getPosition();
	Vector2f direction = m_entity->getComponent<Transform2D>().getRotation();
	pos += m_baseVelo + m_velocity;
	m_velocity += m_acceleration;
	m_velocity.y += m_gravity;
	m_entity->getComponent<Transform2D>().setPosition(pos);*/
}

void Physics2D::render() {

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

void Physics2D::setVelocity(Vector2f velocity) {
	m_velocity = velocity;
}

Vector2f Physics2D::getBaseVelocity() {
	return m_baseVelo;
}

void Physics2D::setBaseVelocity(Vector2f v0) {
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

void Physics2D::addVelocity(Vector2f v0) {
	m_velocity += v0;
}

Vector2f Physics2D::getAcceleration() {
	return m_acceleration;
}

void Physics2D::setAcceleration(Vector2f acceleration) {
	m_acceleration = acceleration;
}

void Physics2D::setGravity(float gravity) {
	m_gravity = gravity;
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