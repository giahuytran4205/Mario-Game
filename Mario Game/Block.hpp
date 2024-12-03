#pragma once
#include "Common.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Block : public Object {
public:
	enum BlockType {
		TERRAIN,
		BRICK,
		EMPTY_BLOCK,
		QUESTION_BLOCK,
		SMALL_CLOUD,
	};

protected:
	Collision* m_collision;
	Physics2D& m_physics2D;
	BlockType m_type;
	SpriteRenderer m_sprite;

public:
	Block();
	Block(const Vector2f& pos, BlockType type);
	Block(const Texture& texture, const Vector2f& pos, BlockType type);
	~Block();

	void update() override;
	void onHit(bool isDestroy);
	BlockType getType();
};