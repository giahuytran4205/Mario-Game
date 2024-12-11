#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "EventSystem.hpp"
#include <iostream>

class Scene : public Object, public IEventListener {
public:
	Scene() {}
	~Scene() {}
	void update() override {}
	void render() override {}
	void handleEvent(const Event& event) override {}

	void fitBackground(sf::Sprite* sprite, sf::RenderWindow& window)
	{
		if (sprite->getTexture() != nullptr)
		{
			sf::Vector2u textureSize = sprite->getTexture()->getSize();
			sf::Vector2u windowSize = window.getSize();

			float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
			float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

			sprite->setScale(scaleX, scaleY);
		}
	}
};