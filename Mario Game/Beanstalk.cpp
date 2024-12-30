#include "Beanstalk.hpp"
#include "Mario.hpp"
#include "GameManager.hpp"

Beanstalk::Beanstalk(Object* parent) {
	addComponent<Collision>(true);
	setParent(parent);

	m_renderOrder = 2;
	m_growRate = 0.05f;
	m_maxHeight = 0;
	m_isOnGrowUp = false;
	m_isMature = false;
	m_destDepth = 0;
	m_height[0] = 0;
	m_height[1] = 0;

	for (int i = 0; i < 2; i++) {
		m_stalk[i].setParent(this);
		m_treetop[i].setParent(this);

		m_treetop[i].setTexture(TextureManager::getTile("Resources/Animations/Items&Objects.png", IntRect(64, 48, 16, 16)));
		m_treetop[i].setTextureRect(IntRect(0, 0, 16, 0));
		m_treetop[i].setPosition(0, 0);
		m_treetop[i].getComponent<Transform2D>().setSize(16, 16);

		m_stalk[i].setTexture(TextureManager::getTile("Resources/Animations/Items&Objects.png", IntRect(64, 64, 16, 16), true));
		m_stalk[i].setTextureRect(IntRect(0, 0, 16, 0));
		m_stalk[i].setPosition(0, 16);
	}
}

Beanstalk::Beanstalk(const Vector2f& pos, float maxHeight, const Vector2f& destination, Object* parent) : Beanstalk(parent) {
	m_maxHeight = maxHeight;
	m_destination = destination;

	m_transform.setPosition(pos);
	m_transform.setAnchor(0.5, 1);
	m_transform.setSize(2, 1);

	for (int i = 0; i < 2; i++) {
		m_treetop[i].setAnchor(0.5, 1);
		m_stalk[i].setAnchor(0.5, 1);

		m_treetop[i].setPosition(0, -m_transform.height + 16);
		m_stalk[i].setPosition(0, 0);
	}

	m_stalk[1].getComponent<Transform2D>().setWorldPosition(destination);
	m_treetop[1].getComponent<Transform2D>().setWorldPosition(m_stalk[1].getComponent<Transform2D>().getWorldPosition() - Vector2f(0, m_stalk[1].getComponent<Transform2D>().height));
}

Beanstalk::Beanstalk(const FRect& rect, const Vector2f& destination, Object* parent) : Beanstalk({ rect.left, rect.top }, 0, destination, parent) {}

Beanstalk::~Beanstalk() {}

void Beanstalk::update() {
	if (m_isOnGrowUp) {
		if (m_stalk[0].getTextureRect().height < m_maxHeight) {
			m_height[0] += m_growRate * deltaTime.asMilliseconds();
			m_stalk[0].setTextureRect(IntRect(0, 0, 16, max(m_height[0], 0.0f)));
		
		}
		else if (m_stalk[1].getTextureRect().height < m_maxHeight) {
			m_height[1] += m_growRate * deltaTime.asMilliseconds();
			m_stalk[1].setTextureRect(IntRect(0, 0, 16, max(m_height[1], 0.0f)));
		}
		else {
			m_isOnGrowUp = false;
			m_isMature = true;
		}

		for (int i = 0; i < 2; i++) {
			m_treetop[i].getComponent<Transform2D>().setWorldPosition(m_stalk[i].getComponent<Transform2D>().getWorldPosition() - Vector2f(0, m_stalk[i].getTextureRect().height));
			m_treetop[i].setTextureRect(IntRect(0, 0, 16, min(m_stalk[i].getTextureRect().height, 16)));
		}
	}
}

void Beanstalk::onCollisionEnter(Collision& col, const Direction& side) {
	if (col.m_entity->isType<Mario>() && !m_isOnGrowUp && !m_isMature) {
		Mario* mario = col.m_entity->convertTo<Mario>();
		AutoControl& autoControl = col.m_entity->getComponent<AutoControl>();

		growUp();

		mario->getComponent<Collision>().setTrigger(true);
		mario->getComponent<Physics2D>().setEnableGravity(false);

		autoControl.addMoveByDistance(Vector2f(0, -m_maxHeight), 3000, Vector2f(0, 0));
		autoControl.addWaitForMiliseconds(1000);
		autoControl.addMoveByPoint(m_destination, 0, Vector2f(0, 0),
			[&](int time) {
				GameManager::getInstance()->getView().setCenter(mario->getComponent<Transform2D>().getWorldPosition().x, m_destDepth * 240 + 120);
			});
		autoControl.addMoveByDistance(Vector2f(0, -m_maxHeight + 32), 2000, Vector2f(0, 0));
		autoControl.addWaitForMiliseconds(100);
		autoControl.addAction(
			[mario]() {
				mario->getComponent<Collision>().setTrigger(false);
				mario->getComponent<Physics2D>().setEnableGravity(true);
				mario->getComponent<Physics2D>().setBaseVelocity({ 0.1, -0.2 });
			});		
	}
}

void Beanstalk::setDestDepth(int depth) {
	m_destDepth = depth;
}

void Beanstalk::growUp() {
	if (m_isMature)
		return;

	m_isOnGrowUp = true;
}