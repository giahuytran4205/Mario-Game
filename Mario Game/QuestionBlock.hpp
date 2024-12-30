#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "EmptyBlock.hpp"
#include "TextureManager.hpp"
#include "Beanstalk.hpp"

class QuestionBlock : public Block {
private:
	bool m_isEmpty;
	Beanstalk* m_beanstalk;

public:
	QuestionBlock(Environment environment = Environment::OVERWORLD, Object* parent = nullptr);
	~QuestionBlock();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit();
	void setHide(bool isHide);
	void addBeanstalk(Beanstalk* beanstalk);
};