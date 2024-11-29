#pragma once
#include "Object.hpp"
#include "ECS.hpp"

class FlagPole : public Object {
private:
	Sprite m_flag;
	bool m_onLoweringFlag;
	bool m_isLoweredFlag;
	float m_flagSpeed;

public:
	FlagPole();
	FlagPole(const Vector2f& pos, const Vector2f& size = {16, 160});
	FlagPole(float x, float y, float width = 16, float height = 160);
	~FlagPole();

	void update() override;
	void render() override;
	void loweringFlag();
	bool isLoweredFlag();
};