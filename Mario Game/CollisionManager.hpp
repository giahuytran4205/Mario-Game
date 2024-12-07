#include "Collision.hpp"
#include "Physics2D.hpp"
#include "Transform2D.hpp"

class CollisionManager {
private:
	static CollisionManager* m_instance;
	vector<vector<vector<Collision*>>> m_grid;
	int m_width;
	int m_height;
	int m_gridSize;
	static vector<Collision*> m_colliders;

public:
	CollisionManager();
	CollisionManager(const Vector2i& size, int gridSize);
	CollisionManager(int width, int height, int gridSize);
	~CollisionManager();

	static void addCollider(Collision* collider);
	void update();
	void refresh();
	void resize(int width, int height, int gridSize = 16);
	static CollisionManager* getInstance();
};