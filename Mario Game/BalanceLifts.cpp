#include "BalanceLifts.hpp"

BalanceLifts::BalanceLifts(Object* parent) {
	setParent(parent);

	for (int i = 0; i < 2; i++) m_lifts[i].setParent(this);

	m_lifts[0].linkOtherLift(&m_lifts[1]);
	m_lifts[1].linkOtherLift(&m_lifts[0]);

	for (int i = 0; i < 2; i++) {
		m_pivot[i].setParent(this);
		// FRect(1, 6, 7, 7)
		m_pivot[i].getComponent<Transform2D>().setAnchor(0.5, 0);
		m_pivot[i].getComponent<Transform2D>().setSize(16, 16);
	}
	m_pivot[0].addComponent<Collision>(FRect(9, 6, 7, 7));
	m_pivot[1].addComponent<Collision>(FRect(0, 6, 7, 7));

	m_pivot[0].setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(64, 144, 16, 16)));
	m_pivot[1].setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(80, 160, 16, 16)));

	for (int i = 0; i < 3; i++)
		m_cable[i].setParent(this);
	
	m_cable[0].setAnchor(0.5, 0);
	m_cable[2].setAnchor(0.5, 0);

	m_cable[0].setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(64, 160, 16, 16), true));
	m_cable[1].setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(80, 144, 16, 16), true));
	m_cable[2].setTexture(TextureManager::getTile("Resources/Tilesets/Items&Objects.png", IntRect(64, 160, 16, 16), true));
}

BalanceLifts::BalanceLifts(const Vector2f& firstLiftPos, const Vector2f& secondLiftPos, float pivotY, float amplitude, float speed) : BalanceLifts() {
	Vector2f balancePos = (firstLiftPos + secondLiftPos) / 2.0f;
	
	m_transform.setWorldPosition(firstLiftPos.x - 24, pivotY);

	m_lifts[0].getComponent<Transform2D>().setWorldPosition(firstLiftPos);
	m_lifts[1].getComponent<Transform2D>().setWorldPosition(secondLiftPos);

	m_transform.setSize(abs(m_lifts[0].getComponent<Transform2D>().left - m_lifts[1].getComponent<Transform2D>().right), 16);

	setAmplitude(amplitude);
	setSpeed(speed);

	m_pivot[0].setPosition(m_lifts[0].getComponent<Transform2D>().getPosition().x, 0);
	m_pivot[1].setPosition(m_lifts[1].getComponent<Transform2D>().getPosition().x, 0);
	
	m_cable[0].setTextureRect(IntRect(0, 0, 16, abs(firstLiftPos.y - pivotY)));
	m_cable[1].setTextureRect(IntRect(0, 0, abs(firstLiftPos.x - secondLiftPos.x) - 16, 16));
	m_cable[2].setTextureRect(IntRect(0, 0, 16, abs(secondLiftPos.y - pivotY)));

	m_cable[0].setPosition(m_pivot[0].getComponent<Transform2D>().getPosition().x, 16);
	m_cable[1].setPosition(m_pivot[0].getComponent<Transform2D>().getPosition().x + 8, 0);
	m_cable[2].setPosition(m_pivot[1].getComponent<Transform2D>().getPosition().x, 16);
}

BalanceLifts::~BalanceLifts() {}

void BalanceLifts::update() {
	m_cable[0].setTextureRect(IntRect(0, 0, 16, m_lifts[0].getComponent<Transform2D>().getPosition().y - 16));
	m_cable[2].setTextureRect(IntRect(0, 0, 16, m_lifts[1].getComponent<Transform2D>().getPosition().y - 16));
}

void BalanceLifts::onCollisionEnter(Collision& col, const Direction& side) {
	
}

void BalanceLifts::setAmplitude(float amplitude) {
	m_lifts[0].setAmplitude(amplitude);
	m_lifts[1].setAmplitude(amplitude);
}

void BalanceLifts::setSpeed(float speed) {
	m_lifts[0].setSpeed(speed);
	m_lifts[1].setSpeed(speed);
}