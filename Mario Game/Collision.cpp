#include "Collision.hpp"
#include "Transform2D.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
using namespace sf;

void Collision::init() {
	if (!m_entity->hasComponent<Transform2D>()) {
		m_entity->addComponent<Transform2D>();
	}
	else m_collider = &m_entity->getComponent<Transform2D>().getRect();

	CollisionManager::addCollider(this);
}

void Collision::update() {
	
}

void Collision::lateUpdate() {
	
}

Rect<float> Collision::getCollider() {
	return *m_collider;
}

void Collision::onCollisionEnter(Collision& col) {
	m_entity->onCollisionEnter(col);
	col.m_entity->onCollisionEnter(*this);
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
		FloatRect rect = col->getCollider();
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
		FloatRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;

		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				for (Collision* item : m_grid[i][j]) {
					if (col->getCollider().intersects(item->getCollider())) {
						col->onCollisionEnter(*item);
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