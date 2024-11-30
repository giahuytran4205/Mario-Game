#include "Beanstalk.hpp"
#include "Mario.hpp"
#include "GameManager.hpp"

Beanstalk::Beanstalk() {
	addComponent<Collision>(true);

	m_renderOrder = 2;
	m_growRate = 0.005f;
	m_isOnGrowUp = false;
	m_stalk.setParent(this);
	m_treetop.setParent(this);

	Texture* texture1 = new Texture();
	texture1->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(64, 48, 16, 16));
	m_treetop.setTexture(*texture1);
	m_treetop.setPosition(0, 0);
	m_treetop.getComponent<Transform2D>().setSize(16, 16);

	Texture* texture2 = new Texture();
	texture2->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(64, 64, 16, 16));
	texture2->setRepeated(true);
	m_stalk.setTexture(*texture2);
	m_stalk.setTextureRect(IntRect(0, 0, 16, 16));
	m_stalk.setPosition(0, 16);
}

Beanstalk::Beanstalk(const Vector2f& pos, const Vector2f& size) : Beanstalk() {
	m_transform.setPosition(pos);
	m_transform.setAnchor(0.5, 1);
	m_transform.setSize(size);

	m_treetop.setAnchor(0.5, 1);
	m_stalk.setAnchor(0.5, 1);

	m_treetop.setPosition(0, -m_transform.height + 16);
	m_stalk.setPosition(0, 0);
}

Beanstalk::Beanstalk(const FRect& rect) : Beanstalk({ rect.left, rect.top }, { rect.width, rect.height }) {}

Beanstalk::~Beanstalk() {}

void Beanstalk::update() {
	if (m_isOnGrowUp) {
		m_transform.setSize(m_transform.width, m_transform.height + m_growRate * deltaTime.asMilliseconds());
		m_stalk.setTextureRect(IntRect(0, 0, 16, m_transform.height - 16));
		m_treetop.setPosition(0, -m_stalk.getTextureRect().height);
	}
}

void Beanstalk::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>() && !m_isOnGrowUp) {
		growUp();
	}
}

void Beanstalk::growUp() {
	m_isOnGrowUp = true;
}
