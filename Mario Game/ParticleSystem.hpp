#pragma once
#include "Object.hpp"
#include "Animation.hpp"
#include "Particle.hpp"
#include <vector>

class ParticleSystem {
private:
	vector<Particle> m_particles;
	int m_index;
	static ParticleSystem* m_instance;

public:
	ParticleSystem(int numParticles = 20);
	~ParticleSystem();

	static ParticleSystem* getInstance();
	Object& addParticle(const string& path, int duration, const Vector2f& pos = { 0, 0 });
	Object& addParticle(const string& path, const Vector2f& pos = { 0, 0 });
	void resize(int size);
};