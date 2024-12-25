#include "CollisionManager.hpp"
#include "EnemiesGoomba.hpp"
#include <iostream>

vector<Collision*> CollisionManager::m_colliders;

CollisionManager* CollisionManager::m_instance = nullptr;

CollisionManager::CollisionManager() : m_width(0), m_height(0), m_gridSize(0) {
	if (!m_instance)
		m_instance = this;
}

CollisionManager::CollisionManager(const Vector2i& size, int gridSize) : CollisionManager(size.x, size.y, gridSize) {}

CollisionManager::CollisionManager(int width, int height, int gridSize) : m_width(width), m_height(height), m_gridSize(gridSize),
																		  m_grid(height / gridSize + 1, vector<vector<Collision*>>(width / gridSize + 1))
{
	if (!m_instance)
		m_instance = this;
}

CollisionManager::~CollisionManager() {}

void CollisionManager::addCollider(Collision* collision) {
	m_colliders.push_back(collision);
}

void CollisionManager::update() {
	refresh();

	for (auto& row : m_grid) {
		for (auto& v : row) v.clear();
	}

	for (Collision* col : m_colliders) {
		if (!col->isEnable())
			continue;

		FRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;

		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				if (i < 0 || i >= m_grid.size() || j < 0 || j >= m_grid[0].size()) 
					continue;
				m_grid[i][j].push_back(col);
			}
		}
	}

	for (Collision* col : m_colliders) {
		if (!col->m_entity->isActive() || col->m_entity->isDestroyed() || !col->isEnable())
			continue;

		if (col->m_entity->hasComponent<Physics2D>() && !col->m_entity->getComponent<Physics2D>().isElastic())
			continue;

		FRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;
		set<Collision*> checked;
		vector<Collision*> intersectCols;

		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				if (i < 0 || i >= m_grid.size() || j < 0 || j >= m_grid[0].size())
					continue;

				for (Collision* item : m_grid[i][j]) {

					if (item == col || checked.contains(item) || !item->m_entity->isActive() || item->m_entity->isDestroyed() || !col->isEnable())
						continue;

					if (col->getCollider().intersects(item->getCollider())) {

						Transform2D tf1 = col->m_entity->getComponent<Transform2D>();
						Transform2D tf2 = item->m_entity->getComponent<Transform2D>();

						if (tf1.getLastPosition() == tf1.getWorldPosition() && tf2.getLastPosition() == tf2.getWorldPosition())
							continue;

						Direction side = Direction::LEFT;

						bool isTrigger = col->isTrigger() || item->isTrigger();

						if (item->m_entity->hasComponent<Physics2D>()) {
							if (item->m_entity->getComponent<Physics2D>().isElastic()) {
								item->resolveCollide(*col, side, isTrigger);
								side = getOpposite(side);
							}
							else {
								col->resolveCollide(*item, side, isTrigger);
							}
						}
						else {
							col->resolveCollide(*item, side, isTrigger);
						}

						intersectCols.push_back(item);
						checked.insert(item);
					}
				}
			}
		}

		for (auto& item : intersectCols) {
			Direction dir;
			col->getTangentPoint(*item, dir);

			col->onCollisionEnter(*item, dir);
			item->onCollisionEnter(*col, getOpposite(dir));
		}

		col->m_entity->getComponent<Transform2D>().setCenter(col->m_entity->getComponent<Transform2D>().getWorldCenter());
	}
}

void CollisionManager::refresh() {
	m_colliders.erase(remove_if(begin(m_colliders), end(m_colliders),
		[](Collision* col)
		{
			return col->m_entity->toObject()->isDestroyed();
		}),
		end(m_colliders));
}

void CollisionManager::resize(int width, int height, int gridSize) {
	m_width = width;
	m_height = height;
	m_gridSize = gridSize;
	int t = width / gridSize + 1;
	m_grid.assign(height / gridSize + 1, vector<vector<Collision*>>(width / gridSize + 1));
}

CollisionManager* CollisionManager::getInstance() {
	return m_instance;
}