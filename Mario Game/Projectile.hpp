#pragma once
#include "Common.hpp"
#include "Object.hpp"

class Projectile : public Object {
private:
	int m_damage;
	float m_maxDistance;
	int m_age;
	
public:
	Projectile(int damage = 1, int maxDistance = 3000);
	~Projectile();

	int getDamage();
	void setDamage(int damage);
	float getMaxDistance();
	void setMaxDistance(float maxDistance);
	int getAge();
	void update() override;
};