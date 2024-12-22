#pragma once
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Animation.hpp"

class Particle : public Object {
private:
	SpriteRenderer m_sprite;
	float m_duration;

public:
	Particle();
	~Particle();

	void update() override;
	void assign(const string& path, float duration, const Vector2f& pos);
	void assign(const string& path, const Vector2f& pos);
	void setDuration(float duration);
};