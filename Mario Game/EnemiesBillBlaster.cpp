#include "EnemiesBillBlaster.hpp"
#include "GameManager.hpp"

EnemiesBillBlaster::EnemiesBillBlaster(Mario& mario, Object* parent) : Enemy(parent), m_mario(mario) {
	m_transform.setSize(16, 16);
	m_sprite.setTexture(TextureManager::getTexture("Resources/Tilesets/BillBlaster.png"));
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(4);
	m_transform.setAnchor(0, 0);

	m_physics.setStatic(true);
	m_physics.setElastic(false);

	m_fireCD = 1500;
	m_curFireCD = 0;
}

void EnemiesBillBlaster::onCollisionEnter(Collision& col, const Direction& side) {
	
}

void EnemiesBillBlaster::hit(bool isDestroy) {

}

void EnemiesBillBlaster::update() {
	float dist = distance(m_mario.getComponent<Transform2D>().getWorldCenter(), m_transform.getWorldCenter());
	float dir = m_mario.getComponent<Transform2D>().getWorldCenter().x - m_transform.getWorldCenter().x;

	if (m_curFireCD > 0)
		m_curFireCD -= deltaTime.asMilliseconds();

	if (dir != 0)
		dir /= abs(dir);

	if (dist < 200) {
		if (dir == -1)
			fire(Direction::LEFT);
		else if (dir == 1)
			fire(Direction::RIGHT);
	}
}

void EnemiesBillBlaster::fire(const Direction& direction) {
	if (m_curFireCD > 0)
		return;

	m_curFireCD = m_fireCD;

	Vector2f dir;
	if (direction == Direction::LEFT)
		dir = { -1, 0 };
	else if (direction == Direction::RIGHT)
		dir = { 1, 0 };

	BulletBill* bullet = new BulletBill(dir);

	if (direction == Direction::LEFT)
		bullet->getComponent<Transform2D>().setWorldPosition(m_transform.getWorldCenter());
	else if (direction == Direction::RIGHT)
		bullet->getComponent<Transform2D>().setWorldPosition(m_transform.getWorldCenter());
}