#include "CollisionManager.hpp"

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
	for (auto& row : m_grid) {
		for (auto& v : row) v.clear();
	}

	for (Collision* col : m_colliders) {
		FRect rect = col->getCollider();
		int right = rect.left + rect.width;
		int bottom = rect.top + rect.height;

		for (int i = rect.top / m_gridSize; i <= bottom / m_gridSize; i++) {
			for (int j = rect.left / m_gridSize; j <= right / m_gridSize; j++) {
				if (i < 0 || i >= m_grid.size() || j < 0 || j >= m_grid[0].size()) 
					return;
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

						if (tf1.getLastPosition() == tf1.getWorldPosition() && tf2.getLastPosition() == tf2.getWorldPosition())
							continue;

						Direction side = Direction::LEFT;

						bool isTrigger = col->isTrigger() || item->isTrigger();

						if (item->m_entity->hasComponent<Physics2D>()) {
							if (item->m_entity->getComponent<Physics2D>().isElastic()) {
								item->resolveCollide(*col, side, isTrigger);
								item->onCollisionEnter(*col, side);
							}
							else {
								col->resolveCollide(*item, side, isTrigger);
								col->onCollisionEnter(*item, side);
							}
						}
						else {
							col->resolveCollide(*item, side, isTrigger);
							col->onCollisionEnter(*item, side);
						}
						
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