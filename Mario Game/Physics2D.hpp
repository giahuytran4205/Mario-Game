#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Physics2D : public Component {
private:
	Vector2f m_baseVelo;
	Vector2f m_velocity;
	Vector2f m_acceleration;
	Vector2f m_startPos;
	float m_mass;
	float m_gravity;
	float m_friction;
	bool m_static;
	bool m_onGround;
	bool m_isBounce;
	Transform2D* m_transform;
	
public:
	Physics2D();
	Physics2D(float gravity, bool isStatic);
	~Physics2D();

	void init() override;
	void update() override;
	void lateUpdate() override;
	void render();
	float getMass();
	void setMass(float mass);
	Vector2f getVelocity();
	void setVelocity(const Vector2f& velocity);
	Vector2f getBaseVelocity();
	void setBaseVelocity(const Vector2f& v0);
	void setBaseVelocityX(float v0x);
	void setBaseVelocityY(float v0y);
	void setVelocityX(float velX);
	void setVelocityY(float velY);
	void addVelocity(const Vector2f& v0);
	Vector2f getAcceleration();
	void setAcceleration(const Vector2f& acceleration);
	void setGravity(float gravity);
	void setStatic(bool isStatic);
	float getFriction();
	void setFriction(float friction);
	void bounce(float velY);
};