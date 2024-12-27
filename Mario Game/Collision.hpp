#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "CollisionManager.hpp"
#include "Transform2D.hpp"
#include "Physics2D.hpp"
#include "Rect.hpp"
#include "Line.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Collision : public Component {
private:
	Transform2D* m_transform;
	FRect* m_collider;
	FRect m_localCol;
	bool m_isTrigger;
	bool m_isUseOwnCollider;
	
	bool m_isSkipResolveCollide{ false };

public:
	Collision(bool isTrigger = false);
	Collision(const FRect& collider, bool isTrigger = false);
	~Collision();

	void init() override;
	void update() override;
	void lateUpdate() override;
	void resolveCollide(Collision& col, Direction& side, bool isTrigger);
	void onCollisionEnter(Collision& col, const Direction& side);
	void setTrigger(bool isTrigger);
	bool isTrigger();
	FRect getCollider() const;
	Vector2f getTangentPoint(const Collision& col, Direction& side) const;

	// Getter and Setter
	bool isSkipResolveCollide() const;
	void setSkipResolveCollide(bool isSkipResolveCollide);
};