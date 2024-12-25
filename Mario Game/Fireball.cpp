#include "Fireball.hpp"
#include "Block.hpp"
#include "ParticleSystem.hpp"
#include "QuestionBlock.hpp"
#include "GameManager.hpp"

Fireball::Fireball(Object* parent, const Vector2f& direction) : Projectile(parent), m_sound(addComponent<SoundComponent>()) {
	m_transform.setSize(8, 8);
	m_anim.loadFromJsonFile("Resources/Animations/Fireball.json");
	m_anim.play(0);
	m_speed = 0.25f;
	setDirection(direction);
	m_age = 5000;
	m_sound.setSoundBuf(SoundBufferManager::getInstance()->getSoundBuf(SoundTrack::FIREBALL));
	m_sound.play();
}

Fireball::~Fireball() {};

void Fireball::update() {
	m_age -= deltaTime.asMilliseconds();
	if (m_age <= 0)
		destroy();
}

void Fireball::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isDerivedFrom<Block>() && !col.m_entity->convertTo<Block>()->isHidden()) {
		if (side == Direction::DOWN) {
			m_physics.setVelocity({ 0, 0 });
			m_physics.setBaseVelocity(Vector2f(m_speed * m_direction.x, -0.15f));
		}
		else {
			Object& particle = ParticleSystem::getInstance()->addParticle("Resources/Particles/FireballParticle.json", m_transform.getWorldCenter());
			particle.getComponent<Physics2D>().setEnableGravity(false);
			destroy();
		}
	}
}