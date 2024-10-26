#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace sf;
using namespace std;

class Collision : public Component {
private:
	Rect<float>* m_collider;
	static vector<Collision*> m_colliders;

public:
	void init() override;
	void update() override;
	void lateUpdate() override;
	Rect<float> getCollider();
	void onCollisionEnter(Collision& col);
};