#include "MapSelectionScene.hpp"
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

sf::Vector2f MapSelectionScene::getMap1ButtonSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 5.f, window.getSize().y / 8.0f };
}

sf::Vector2f MapSelectionScene::getMap2ButtonSize(sf::RenderWindow& window)
{
	return getMap1ButtonSize(window);
}

sf::Vector2f MapSelectionScene::getMap3ButtonSize(sf::RenderWindow& window)
{
	return getMap2ButtonSize(window);
}

sf::Vector2f MapSelectionScene::getMap4ButtonSize(sf::RenderWindow& window)
{
	return getMap3ButtonSize(window);
}

sf::Vector2f MapSelectionScene::getMap5ButtonSize(sf::RenderWindow& window)
{
	return getMap4ButtonSize(window);
}

sf::Vector2f MapSelectionScene::getMap1ButtonPosition(sf::RenderWindow& window)
{
	return { window.getSize().x / 2.0f - getMap1ButtonSize(window).x / 2.0f, window.getSize().y / 4.0f - getMap1ButtonSize(window).y };
}

sf::Vector2f MapSelectionScene::getMap2ButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getMap1ButtonPosition(window);
	position.y += getMap1ButtonSize(window).y + MAPSELECTIONSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f MapSelectionScene::getMap3ButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getMap2ButtonPosition(window);
	position.y += getMap2ButtonSize(window).y + MAPSELECTIONSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f MapSelectionScene::getMap4ButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getMap3ButtonPosition(window);
	position.y += getMap3ButtonSize(window).y + MAPSELECTIONSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f MapSelectionScene::getMap5ButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getMap4ButtonPosition(window);
	position.y += getMap4ButtonSize(window).y + MAPSELECTIONSCENE_SPACE_DISTANCE;
	return position;
}

MapSelectionScene::MapSelectionScene()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	// SET BACKGROUND
	m_background.setTexture(TextureManager::getTexture("Resources/Background/MarioBros-Background.png"));
	this->fitBackground(&m_background, window);

	// CALCULATE SIZE & POSITION
	sf::Vector2f map1ButtonSize = getMap1ButtonSize(window);
	sf::Vector2f map2ButtonSize = getMap2ButtonSize(window);
	sf::Vector2f map3ButtonSize = getMap3ButtonSize(window);
	sf::Vector2f map4ButtonSize = getMap4ButtonSize(window);
	sf::Vector2f map5ButtonSize = getMap5ButtonSize(window);

	sf::Vector2f map1ButtonPosition = getMap1ButtonPosition(window);
	sf::Vector2f map2ButtonPosition = getMap2ButtonPosition(window);
	sf::Vector2f map3ButtonPosition = getMap3ButtonPosition(window);
	sf::Vector2f map4ButtonPosition = getMap4ButtonPosition(window);
	sf::Vector2f map5ButtonPosition = getMap5ButtonPosition(window);

	// SET BUTTONS
	m_map1.configure(map1ButtonPosition, map1ButtonSize, "MAP 1", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MAP 1" << std::endl;
		});
	m_map2.configure(map2ButtonPosition, map2ButtonSize, "MAP 2", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MAP 2" << std::endl;
		});
	m_map3.configure(map3ButtonPosition, map3ButtonSize, "MAP 3", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MAP 3" << std::endl;
		});
	m_map4.configure(map4ButtonPosition, map1ButtonSize, "MAP 4", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MAP 4" << std::endl;
		});
	m_map5.configure(map5ButtonPosition, map5ButtonSize, "MAP 5", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MAP 5" << std::endl;
		});

	// SET RENDER ORDER
	m_map1.setRenderOrder(10);
	m_map1.setTextViewRenderOrder(20);
	m_map2.setRenderOrder(10);
	m_map2.setTextViewRenderOrder(20);
	m_map3.setRenderOrder(10);
	m_map3.setTextViewRenderOrder(20);
	m_map4.setRenderOrder(10);
	m_map4.setTextViewRenderOrder(20);
	m_map5.setRenderOrder(10);
	m_map5.setTextViewRenderOrder(20);
}

MapSelectionScene::~MapSelectionScene()
{
}

void MapSelectionScene::update()
{
}

void MapSelectionScene::render()
{
}

void MapSelectionScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized)
	{
		// ... Finish Later
	}
}
