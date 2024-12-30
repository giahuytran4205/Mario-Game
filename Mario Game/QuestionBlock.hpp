#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "EmptyBlock.hpp"
#include "TextureManager.hpp"

class QuestionBlock : public Block {
private:
	bool m_isEmpty;
	bool m_containBeanstalk;

public:
	QuestionBlock(Environment environment = Environment::OVERWORLD, Object* parent = nullptr);
	~QuestionBlock();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit();
	void setHide(bool isHide);
	void addBeanstalk();
};