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
	const Vector2f& getVelocity();
	void setVelocity(const Vector2f& velocity);
	const Vector2f& getBaseVelocity();
	void setBaseVelocity(const Vector2f& v0);
	void setBaseVelocityX(const float& v0x);
	void setBaseVelocityY(const float& v0y);
	void setVelocityX(const float& velX);
	void setVelocityY(const float& velY);
	void addVelocity(const Vector2f& v0);
	const Vector2f& getAcceleration();
	void setAcceleration(const Vector2f& acceleration);
	void setGravity(const float& gravity);
	void setStatic(const bool& isStatic);
	const float& getFriction();
	void setFriction(const float& friction);
};