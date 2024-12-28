#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "EmptyBlock.hpp"
#include "TextureManager.hpp"
#include "Random.hpp"

class QuestionBlock : public Block {
private:
	bool m_isEmpty;
	RandomQuestion::Type mType{ RandomQuestion::UNKNOW };
	std::shared_ptr<RandomQuestion> mRadom{ nullptr };
public:
	QuestionBlock(Environment environment = Environment::OVERWORLD, 
		Object* parent = nullptr, 
		const RandomQuestion::Type type = RandomQuestion::COIN);
	~QuestionBlock();

	void onCollisionEnter(Collision& col, const Direction& side) override;
	void hit();
	void setHide(bool isHide);

	void setRandom(std::shared_ptr<RandomQuestion> radom);
	void setFixType(RandomQuestion::Type type);
};