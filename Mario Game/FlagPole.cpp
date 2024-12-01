#include "FlagPole.hpp"
#include "Collision.hpp"
#include "GameManager.hpp"
#include <iostream>

FlagPole::FlagPole(Object* parent) : m_sound(addComponent<SoundComponent>()) {
	addComponent<Collision>(true);
	setParent(parent);
	
	m_transform.setPosition(0, 0);
	m_transform.setAnchor(0.5, 0);
	m_transform.setSize(16, 160);

	Texture* texture = new Texture();
	texture->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(128, 16, 16, 16));
	m_flag.setTexture(*texture);
	m_flag.getComponent<Transform2D>().setAnchor(1, 0);

	Texture* texture2 = new Texture();
	texture2->loadFromFile("Resources/Map/Worlds-1-1.json", IntRect(3168, 32, 16, 16));
	m_pole.setTexture(*texture2);
	m_pole.getComponent<Transform2D>().setAnchor(0.5, 0);

	Texture* texture3 = new Texture();
	texture3->loadFromFile("Resources/Tilesets/Tileset-1.png", { 256, 144, 16, 16 });
	texture3->setRepeated(true);
	m_pole1.setTexture(*texture3);
	m_pole1.setTextureRect(IntRect(0, 0, 16, 144));
	m_pole1.getComponent<Transform2D>().setAnchor(0.5, 0);

	m_onLoweringFlag = false;
	m_isLoweredFlag = false;
	m_flagSpeed = 0.1f;
	m_renderOrder = 2;
}

FlagPole::FlagPole(const Vector2f& pos, const Vector2f& size, Object* parent) : FlagPole(pos.x, pos.y, size.x, size.y, parent) {}

FlagPole::FlagPole(float x, float y, float width, float height, Object* parent) : FlagPole(parent) {
	m_transform.setPosition(x, y);
	m_transform.setSize(width, height);

	m_flag.getComponent<Transform2D>().setPosition(x, y + 16);
	m_pole.getComponent<Transform2D>().setPosition(x, y);
	
	m_pole1.getComponent<Transform2D>().setPosition(x, y + 16);
}

FlagPole::~FlagPole() {}

void FlagPole::update() {
	if (m_onLoweringFlag) {
		Vector2f pos = m_flag.getPosition();
		pos.y += m_flagSpeed * deltaTime.asMilliseconds();

		if (pos.y >= m_transform.bottom - 16) {
			pos.y = m_transform.bottom - 16;
			m_onLoweringFlag = false;
			m_isLoweredFlag = true;
		}

		m_flag.getComponent<Transform2D>().setPosition(pos);
	}
}

void FlagPole::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_pole);
	GameManager::getInstance()->getRenderWindow().draw(m_flag);
}

void FlagPole::loweringFlag() {
	m_onLoweringFlag = true;
	m_sound.play(SoundTrack::FLAGPOLE);
}

bool FlagPole::isOnLoweringFlag() {
	return m_onLoweringFlag;
}

bool FlagPole::isLoweredFlag() {
	return m_isLoweredFlag;
}