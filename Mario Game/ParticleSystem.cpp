#include "ParticleSystem.hpp"

ParticleSystem* ParticleSystem::m_instance = nullptr;

ParticleSystem::ParticleSystem(int numParticles) : m_particles(numParticles) {
	if (!m_instance)
		m_instance = this;

	m_index = 0;
}

ParticleSystem::~ParticleSystem() {}

ParticleSystem* ParticleSystem::getInstance() {
	return m_instance;
}

Object& ParticleSystem::addParticle(const string& path, int duration, const Vector2f& pos) {
	int lastIndex = m_index;
	m_particles[lastIndex].assign(path, duration, pos);
	++m_index %= m_particles.size();
	return m_particles[lastIndex];
}

Object& ParticleSystem::addParticle(const string& path, const Vector2f& pos) {
	int lastIndex = m_index;
	m_particles[lastIndex].assign(path, pos);
	++m_index %= m_particles.size();
	return m_particles[lastIndex];
}

void ParticleSystem::resize(int size) {
	m_particles.resize(size);
}