#include "Beanstalk.hpp"
#include "Mario.hpp"
#include "GameManager.hpp"

Beanstalk::Beanstalk(Object* parent) {
	addComponent<Collision>(true);
	setParent(parent);

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

Beanstalk::Beanstalk(const Vector2f& pos, const Vector2f& size, const Vector2f& destination, Object* parent) : Beanstalk(parent) {
	m_transform.setPosition(pos);
	m_transform.setAnchor(0.5, 1);
	m_transform.setSize(size);

	m_treetop.setAnchor(0.5, 1);
	m_stalk.setAnchor(0.5, 1);

	m_treetop.setPosition(0, -m_transform.height + 16);
	m_stalk.setPosition(0, 0);
}

Beanstalk::Beanstalk(const FRect& rect, const Vector2f& destination, Object* parent) : Beanstalk({ rect.left, rect.top }, { rect.width, rect.height }, destination, parent) {}

Beanstalk::~Beanstalk() {}

void Beanstalk::update() {
	if (m_isOnGrowUp) {
		Transform2D& stalkTF = m_stalk.getComponent<Transform2D>();

		stalkTF.setHeight(stalkTF.height + m_growRate * deltaTime.asMilliseconds());
		m_stalk.setTextureRect(IntRect(0, 0, 16, m_transform.height - 16));
		m_treetop.setPosition(0, -m_stalk.getTextureRect().height);

		if (m_treetop.getComponent<Transform2D>().top >= m_transform.top) {
			m_isOnGrowUp = false;
		}
	}
}

void Beanstalk::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>() && !m_isOnGrowUp) {
		Mario* mario = col.m_entity->convertTo<Mario>();
		AutoControl& autoControl = col.m_entity->getComponent<AutoControl>();

		growUp();

		autoControl.addMoveByDistance(Vector2f(0, m_destination.y - mario->getComponent<Transform2D>().getPosition().y), 3000, Vector2f(0, 0),
			[](int time) {

			});
		autoControl.addWaitForMiliseconds(1000);
		autoControl.addAction([&]() { mario->getComponent<Physics2D>().setBaseVelocity({ 0.005, -0.005 }); });
	}
}

void Beanstalk::growUp() {
	m_isOnGrowUp = true;
}