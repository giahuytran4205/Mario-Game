#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "Transform2D.hpp"
using namespace sf;

class SpriteRenderer : public Component {
private:
	Sprite m_sprite;
	//Transform2D& m_transform;
public:
	SpriteRenderer();
	~SpriteRenderer();

	void update() override;
	void render() override;
	Sprite& getSprite();
	void setTexture(Texture& texture);
	void setTexture(Texture& texture, const IntRect& rectangle);
};