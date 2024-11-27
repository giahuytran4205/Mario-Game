#include "Collision.hpp"
#include "Transform2D.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include "Line.hpp"
#include "Physics2D.hpp"
#include <vector>
#include <iostream>
using namespace sf;

Collision::Collision() {}

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

	if (rect.contains(bodyTF.getLastPosition()) && rect.contains(bodyTF.getPosition())) {
		bodyTF.adjustPosition(Vector2f(bodyTF.getPosition().x, colTF.getRect().top - m_collider->height / 2));
		return;
	}

	int side;
	Vector2f tangentPoint = getTangentPoint(col, side);

	bodyTF.adjustPosition(tangentPoint);
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

						if (tf1.getLastPosition() == tf1.getPosition()) {
							item->resolveCollide(*col);
						}
						else col->resolveCollide(*item);

						col->onCollisionEnter(*item);
						item->onCollisionEnter(*col);
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