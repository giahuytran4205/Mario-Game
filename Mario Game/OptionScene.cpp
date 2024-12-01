#include "OptionScene.hpp"

OptionScene::OptionScene()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	// SLIDER
}

OptionScene::~OptionScene()
{
}

void OptionScene::update()
{
}

void OptionScene::render()
{
}

void OptionScene::handleEvent(const sf::Event& event)
{
}
