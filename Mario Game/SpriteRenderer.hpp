#pragma once
#include "Common.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
#include "Transform2D.hpp"
#include "Object.hpp"
using namespace sf;

class SpriteRenderer : public Object, public Sprite {
private:

public:
	SpriteRenderer(Object* parent = nullptr);
	~SpriteRenderer();

	SpriteRenderer& operator=(const SpriteRenderer& other);

	void update() override;
	void render() override;
	Sprite& getSprite();
	void setPosition(const Vector2f& pos);
	void setPosition(float x, float y);
	void setAnchor(const Vector2f& anchor);
	void setAnchor(float anchorX, float anchorY);
};