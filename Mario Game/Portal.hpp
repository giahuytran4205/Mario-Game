#pragma once
#include "Block.hpp"
#include "SFML/Graphics.hpp"
#include "Collision.hpp"
using namespace sf;

class Portal : public Object {
private:
	Vector2f m_destination;
	Collision& m_collision;
	int m_inDirection;
	int m_outDirection;
	int m_destDepth;

public:
	Portal();
	Portal(const Vector2f& position, const Vector2f& destination, int inDir, int outDir, int destDepth);
	Portal(const Portal& portal);
	~Portal();

	Portal& operator=(const Portal& portal);

	const Vector2f& getDestination();
	Keyboard::Key getEnterKey();
	Vector2f getInDirection();
	Vector2f getOutDirection();
	int getDestDepth();
};