#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Physics2D : public Component {
private:
	float m_mass;
	Vector2f m_baseVelo;
	Vector2f m_velocity;
	Vector2f m_acceleration;
	float m_gravity;
	float m_friction;
	bool m_static;
	
public:
	void init() override;
	void update() override;
	void lateUpdate() override;
	void render();
	float getMass();
	void setMass(float mass);
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
	Vector2f getBaseVelocity();
	void setBaseVelocity(Vector2f v0);
	void setBaseVelocityX(float v0x);
	void setBaseVelocityY(float v0y);
	void setVelocityX(float velX);
	void setVelocityY(float velY);
	void addVelocity(Vector2f v0);
	Vector2f getAcceleration();
	void setAcceleration(Vector2f acceleration);
	void setGravity(float gravity);
	void setStatic(bool isStatic);
	float getFriction();
	void setFriction(float friction);
};