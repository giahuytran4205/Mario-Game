#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "Rect.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Collision : public Component {
public:
	FRect* m_collider;
	void resolveCollide(Collision& col);

public:
	Collision();
	~Collision();

	void init() override;
	void update() override;
	void lateUpdate() override;
	FRect getCollider();
	void onCollisionEnter(Collision& col);
	Vector2f getTangentPoint(const Collision& col, int& side) const;
};

class CollisionManager {
private:
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
};