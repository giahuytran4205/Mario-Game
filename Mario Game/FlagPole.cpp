#include "FlagPole.hpp"
#include "Collision.hpp"
#include "GameManager.hpp"
#include <iostream>

FlagPole::FlagPole() {
	addComponent<Collision>(true);
	
	m_transform.setPosition(0, 0);
	m_transform.setAnchor(0, 0);
	m_transform.setSize(16, 160);

	Texture* texture = new Texture();
	texture->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(128, 16, 16, 16));
	m_flag.setTexture(*texture);

	Texture* texture2 = new Texture();
	texture2->loadFromFile("D:/GHuy/OOP/Tile/Mario/Mario/Worlds-1-1.png", IntRect(3168, 32, 16, 160));
	m_pole.setTexture(*texture2);

	m_onLoweringFlag = false;
	m_isLoweredFlag = false;
	m_flagSpeed = 0.1f;
	m_renderOrder = 2;
}

FlagPole::FlagPole(const Vector2f& pos, const Vector2f& size) : FlagPole(pos.x, pos.y, size.x, size.y) {}

FlagPole::FlagPole(float x, float y, float width, float height) : FlagPole() {
	m_transform.setPosition(x, y);
	//m_transform.setAnchor(0.5, 0);
	m_transform.setSize(width, height);

	m_flag.setPosition(x - 8, m_transform.top + 16);
	m_pole.setPosition(m_transform.left, m_transform.top);
}

FlagPole::~FlagPole() {}

void FlagPole::update() {
	
	//std::cout << m_onLoweringFlag << '\n';
	if (m_onLoweringFlag) {
		Vector2f pos = m_flag.getPosition();
		pos.y += m_flagSpeed * deltaTime.asMilliseconds();

		if (pos.y >= m_transform.bottom - 8) {
			pos.y = m_transform.bottom - 8;
			m_onLoweringFlag = false;
		}

		m_flag.setPosition(pos);
	}
}

void FlagPole::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_pole);
	GameManager::getInstance()->getRenderWindow().draw(m_flag);
}

void FlagPole::loweringFlag() {
	m_onLoweringFlag = true;
	m_isLoweredFlag = true;
}

bool FlagPole::isLoweredFlag() {
	return m_isLoweredFlag;
}