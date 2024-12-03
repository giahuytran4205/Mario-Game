#include "Collision.hpp"
#include "Transform2D.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include "Line.hpp"
#include "Physics2D.hpp"
#include <vector>
#include <iostream>
using namespace sf;

Collision::Collision(bool isTrigger) : m_isTrigger(isTrigger) {}

Collision::~Collision() {}

void Collision::init() {
	if (!m_entity->hasComponent<Transform2D>()) {
		m_entity->addComponent<Transform2D>();
	}
	else m_collider = &m_entity->getComponent<Transform2D>().getRect();

	CollisionManager::addCollider(this);
}

void Collision::resolveCollide(Collision& col) {
	Transform2D& colTF = col.m_entity->getComponent<Transform2D>();
	Transform2D& bodyTF = m_entity->getComponent<Transform2D>();

	FRect rect = colTF.getRect();
	rect = {rect.left - m_collider->width / 2, rect.top - m_collider->height / 2, rect.width + m_collider->width, rect.height + m_collider->height};

	Vector2f colVel, bodyVel;
	if (col.m_entity->hasComponent<Physics2D>()) {
		colVel = col.m_entity->getComponent<Physics2D>().getVelocity() + col.m_entity->getComponent<Physics2D>().getBaseVelocity();
	}

	if (m_entity->hasComponent<Physics2D>()) {
		bodyVel = m_entity->getComponent<Physics2D>().getVelocity() + m_entity->getComponent<Physics2D>().getBaseVelocity();
	}

	if (col.m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = col.m_entity->getComponent<Physics2D>();
		physics.setBaseVelocity({ 0, 0 });
		physics.setVelocity({ 0, 0 });
	}

	if (m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = m_entity->getComponent<Physics2D>();
		physics.setBaseVelocity({ 0, 0 });
		physics.setVelocity({ 0, 0 });
	}


	if (rect.contains(bodyTF.getLastPosition()) && rect.contains(bodyTF.getPosition())) {
		if (colVel.y <= 0)
			bodyTF.setPosition(bodyTF.getPosition().x, colTF.top - m_collider->height / 2);
		else {
			bodyTF.setPosition(bodyTF.getPosition().x, colTF.bottom + m_collider->height / 2);
			
			if (m_entity->hasComponent<Physics2D>()) {
				Physics2D& physics = m_entity->getComponent<Physics2D>();
				physics.setBaseVelocityY(colVel.y + 0.05);
			}
			
		}

		return;
	}

	int side;
	Vector2f tangentPoint = getTangentPoint(col, side);
	Vector2f vel = bodyTF.getPosition() - tangentPoint;
	if (side == 0 || side == 2)
		vel.x = 0;
	else vel.y = 0;

	if (m_entity->hasComponent<Physics2D>()) {
		Physics2D& physics = m_entity->getComponent<Physics2D>();

		if (side == 3)
			physics.setBaseVelocityY(colVel.y + 0.05);
		if (side == 0 || side == 2)
			physics.setBaseVelocityY(0.1f);
	}

	bodyTF.adjustPosition(tangentPoint + vel);
}

void Collision::update() {
	
}

void Collision::lateUpdate() {
	
}

FRect Collision::getCollider() {
	return *m_collider;
}

void Collision::onCollisionEnter(Collision& col) {
	m_entity->onCollisionEnter(col);
	col.m_entity->onCollisionEnter(*this);
}

void Collision::setTrigger(bool isTrigger) {
	m_isTrigger = isTrigger;
}

bool Collision::isTrigger() {
	return m_isTrigger;
}

Vector2f Collision::getTangentPoint(const Collision& col, int& side) const {
	Line line(m_entity->getComponent<Transform2D>().getLastPosition(), m_entity->getComponent<Transform2D>().getPosition());

	FRect rect = col.m_entity->getComponent<Transform2D>().getRect();
	FRect bodyRect = m_entity->getComponent<Transform2D>().getRect();

	rect = { rect.left - bodyRect.width / 2, rect.top - bodyRect.height / 2, rect.width + bodyRect.width, rect.height + bodyRect.height };
	return line.raycast(rect, side);
}

vector<Collision*> CollisionManager::m_colliders;

CollisionManager::CollisionManager() : m_width(0), m_height(0), m_gridSize(0) { }

CollisionManager::CollisionManager(const Vector2i& size, int gridSize) : CollisionManager(size.x, size.y, gridSize) { }

CollisionManager::CollisionManager(int width, int height, int gridSize)	:	m_width(width), m_height(height), m_gridSize(gridSize),
																			m_grid(height / gridSize + 1, vector<vector<Collision*>>(width / gridSize + 1))
{
	
}

CollisionManager::~CollisionManager() { }

void CollisionManager::addCollider(Collision* collision) {
	m_colliders.push_back(collision);
}

void CollisionManager::update() {
	for (auto& row : m_grid) {
		for (auto& v : row) v.clear();
	}
	
	for (Collision* col : m_colliders) {
		FRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;


		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				if (i < 0 || i >= m_grid.size() || j < 0 || j >= m_grid[0].size()) return;
				m_grid[i][j].push_back(col);
			}
		}
	}

	for (Collision* col : m_colliders) {
		FRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;

		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				for (Collision* item : m_grid[i][j]) {

					if (item == col) continue;

					if (col->getCollider().intersects(item->getCollider())) {
						Transform2D tf1 = col->m_entity->getComponent<Transform2D>();
						Transform2D tf2 = item->m_entity->getComponent<Transform2D>();

						if (tf1.getLastPosition() == tf1.getPosition() && tf2.getLastPosition() == tf2.getPosition())
							continue;

						if (!col->isTrigger() && !item->isTrigger()) {
							if (item->m_entity->hasComponent<Physics2D>()) {
								if (item->m_entity->getComponent<Physics2D>().isElastic())
									item->resolveCollide(*col);
								else col->resolveCollide(*item);
							}
							else col->resolveCollide(*item);
						}

						col->onCollisionEnter(*item);
						//item->onCollisionEnter(*col);
					}
				}
			}
		}
	}

	refresh();
}

void CollisionManager::refresh() {
	m_colliders.erase(remove_if(begin(m_colliders), end(m_colliders),
		[](Collision* col)
		{
			return !col->m_entity->isActive();
		}),
		end(m_colliders));
}