#pragma once
#include "Object.hpp"
#include "ECS.hpp"
#include "SpriteRenderer.hpp"
#include "SoundComponent.hpp"

class FlagPole : public Object {
private:
	SpriteRenderer m_flag;
	SpriteRenderer m_pole;
	SpriteRenderer m_pole1;
	bool m_onLoweringFlag;
	bool m_isLoweredFlag;
	float m_flagSpeed;
	SoundComponent& m_sound;

public:
	FlagPole();
	FlagPole(const Vector2f& pos, const Vector2f& size = {16, 160});
	FlagPole(float x, float y, float width = 16, float height = 160);
	~FlagPole();

	void update() override;
	void render() override;
	void loweringFlag();
	bool isOnLoweringFlag();
	bool isLoweredFlag();
};