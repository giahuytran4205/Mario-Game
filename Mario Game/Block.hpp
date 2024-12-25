#pragma once
#include "Common.hpp"
#include "Object.hpp"
#include "Enum.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Block : public Object {
protected:
	Physics2D& m_physics2D;
	SpriteRenderer m_sprite;
	Environment m_environment;
	bool m_isHide;

public:
	Block(Object* parent = nullptr);
	Block(const Vector2f& pos);
	Block(const Texture& texture, const Vector2f& pos);
	Block(const Block& block);
	~Block();

	Block& operator=(const Block& block);

	void update() override;
	void onHit(bool isDestroy);
	bool isHidden() const;
};