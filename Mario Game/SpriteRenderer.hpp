#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class SpriteRenderer : public Component {
private:
	Sprite m_sprite;
public:
	SpriteRenderer();
	~SpriteRenderer();

	void update() override;
	void render() override;
	Sprite& getSprite();
	void setTexture(Texture& texture);
	void setTexture(Texture& texture, const IntRect& rectangle);
};