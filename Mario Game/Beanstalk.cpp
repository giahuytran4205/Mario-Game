#include "Beanstalk.hpp"
#include "Mario.hpp"
#include "GameManager.hpp"

Beanstalk::Beanstalk(Object* parent) {
	addComponent<Collision>(true);
	setParent(parent);

	m_renderOrder = 2;
	m_growRate = 0.005f;
	m_height = 0;
	m_isOnGrowUp = false;
	m_isMature = false;
	m_stalk.setParent(this);
	m_treetop.setParent(this);

	Texture* texture1 = new Texture();
	texture1->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(64, 48, 16, 16));
	m_treetop.setTexture(*texture1);
	m_treetop.setTextureRect(IntRect(0, 0, 16, 0));
	m_treetop.setPosition(0, 0);
	m_treetop.getComponent<Transform2D>().setSize(16, 16);

	Texture* texture2 = new Texture();
	texture2->loadFromFile("Resources/Animations/Items&Objects.png", IntRect(64, 64, 16, 16));
	texture2->setRepeated(true);
	m_stalk.setTexture(*texture2);
	m_stalk.setTextureRect(IntRect(0, 0, 16, 0));
	m_stalk.setPosition(0, 16);
}

Beanstalk::Beanstalk(const Vector2f& pos, float height, const Vector2f& destination, Object* parent) : Beanstalk(parent) {
	m_height = height;

	m_transform.setPosition(pos);
	m_transform.setAnchor(0.5, 1);
	m_transform.setSize(2, 1);

	m_treetop.setAnchor(0.5, 1);
	m_stalk.setAnchor(0.5, 1);

	m_treetop.setPosition(0, -m_transform.height + 16);
	m_stalk.setPosition(0, 0);
}

Beanstalk::Beanstalk(const FRect& rect, const Vector2f& destination, Object* parent) : Beanstalk({ rect.left, rect.top }, 0, destination, parent) {}

Beanstalk::~Beanstalk() {}

void Beanstalk::update() {
	if (m_isOnGrowUp) {
		Transform2D& stalkTF = m_stalk.getComponent<Transform2D>();

		m_transform.setHeight(m_transform.height + m_growRate * deltaTime.asMilliseconds());
		m_stalk.setTextureRect(IntRect(0, 0, 16, max(m_transform.height - 16, 0.0f)));
		m_treetop.setPosition(0, -m_stalk.getTextureRect().height);
		m_treetop.setTextureRect(IntRect(0, 0, 16, min(m_transform.height, 16.0f)));

		if (m_stalk.getTextureRect().height >= m_height) {
			m_isOnGrowUp = false;
			m_isMature = true;
		}
	}
}

void Beanstalk::onCollisionEnter(Collision& col) {
	if (col.m_entity->isType<Mario>() && !m_isOnGrowUp && !m_isMature) {
		Mario* mario = col.m_entity->convertTo<Mario>();
		AutoControl& autoControl = col.m_entity->getComponent<AutoControl>();

		growUp();

		mario->getComponent<Collision>().setTrigger(true);
		mario->getComponent<Physics2D>().setEnableGravity(false);

		autoControl.addMoveByDistance(Vector2f(0, -100), 3000, Vector2f(0, 0));
		autoControl.addWaitForMiliseconds(100);
		autoControl.addAction(
			[mario]() {
				mario->getComponent<Collision>().setTrigger(false);
				mario->getComponent<Physics2D>().setEnableGravity(true);
				mario->getComponent<Physics2D>().setBaseVelocity({ 0.1, -0.2 });
			});		
	}
}

void Beanstalk::growUp() {
	if (m_isMature)
		return;

	m_isOnGrowUp = true;
}