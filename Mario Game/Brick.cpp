#include "Brick.hpp"
#include "SceneManager.hpp"

Brick::Brick(Environment environment,Object* parent) : Block(parent) {
	m_transform.setSize(16, 16);
	m_environment = environment;

	if (environment == Environment::OVERWORLD)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 0, 16, 16)));
	if (environment == Environment::UNDERGROUND)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 32, 16, 16)));
	if (environment == Environment::ATHLETIC)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 0, 16, 16)));
	if (environment == Environment::CASTLE)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 64, 16, 16)));
	if (environment == Environment::UNDERWATER)
		m_sprite.setTexture(TextureManager::getTile("Resources/Tilesets/Tileset-1.png", IntRect(16, 96, 16, 16)));
}

Brick::~Brick() {}

void Brick::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>()) {
		if (side == Direction::DOWN) {
			hit(col.m_entity->convertTo<Mario>()->getAbility() != Mario::Ability::REGULAR);
		}
	}
}

void Brick::hit(bool isDestroy) {
	m_physics2D.bounce(-0.06);
	if (isDestroy) {
		for (int i = 0; i < 4; i++) {
			Vector2f pos(m_transform.left, m_transform.top);
			pos.x += m_transform.getSize().x / 2.0f * (float)(i % 2) + m_transform.getSize().x / 4.0f;
			pos.y += m_transform.getSize().y / 2.0f * (float)(i / 2) + m_transform.getSize().y / 4.0f;

			Object& debris = ParticleSystem::getInstance()->addParticle("Resources/Particles/Debris.json", 1000, pos);
			float randSpeed = randRange(0.08f, 0.12f);
			debris.getComponent<Physics2D>().setBaseVelocity({ cos(PI / 2 * i + PI / 4) * randSpeed, sin(PI / 2 * i + PI / 4) * randSpeed });
			debris.getComponent<Physics2D>().setEnableGravity(true);
			debris.setRenderOrder(5);
		}

		SceneManager::getInstance()->getCurrentScene().getComponent<SoundComponent>().play(SoundTrack::BREAK);

		destroy();
	}
	else {
		SceneManager::getInstance()->getCurrentScene().getComponent<SoundComponent>().play(SoundTrack::BUMP);
	}
}