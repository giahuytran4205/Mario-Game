#include "Particle.hpp"
#include "GameManager.hpp"

Particle::Particle() {
	addComponent<Animation>(m_sprite);
	addComponent<Physics2D>(0.00625 / 8);
	m_transform.setAnchor(0.5, 0.5);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.getComponent<Transform2D>().setSize(8, 8);
	m_sprite.setParent(this);
	m_sprite.setRenderOrder(5);
	m_duration = 0;
	setEnable(false);
}

Particle::~Particle() {

}

void Particle::update() {
	if (m_duration > 0)
		m_duration -= deltaTime.asMilliseconds();
	else
		setEnable(false);
}

void Particle::assign(const string& path, float duration, const Vector2f& pos) {
	getComponent<Animation>().loadFromJsonFile(path);
	getComponent<Animation>().play(0);

	getComponent<Physics2D>().setVelocity({ 0, 0 });
	getComponent<Physics2D>().setBaseVelocity({ 0, 0 });

	m_duration = duration;
	m_transform.setWorldPosition(pos);
	setEnable(true);
}

void Particle::assign(const string& path, const Vector2f& pos) {
	getComponent<Animation>().loadFromJsonFile(path);
	getComponent<Animation>().play(0);

	getComponent<Physics2D>().setVelocity({ 0, 0 });
	getComponent<Physics2D>().setBaseVelocity({ 0, 0 });

	m_duration = getComponent<Animation>().getTrackLength(0);
	m_transform.setWorldPosition(pos);
	setEnable(true);
}

void Particle::setDuration(float duration) {
	m_duration = duration;
}