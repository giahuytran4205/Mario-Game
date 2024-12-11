#include "DifficultyScene.hpp"
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

sf::Vector2f DifficultyScene::getEasyButtonSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 5.f, window.getSize().y / 8.0f };
}

sf::Vector2f DifficultyScene::getMediumButtonSize(sf::RenderWindow& window)
{
	return getEasyButtonSize(window);
}

sf::Vector2f DifficultyScene::getDifficultButtonSize(sf::RenderWindow& window)
{
	return getMediumButtonSize(window);
}

sf::Vector2f DifficultyScene::getEasyButtonPosition(sf::RenderWindow& window)
{
	return { window.getSize().x / 2.0f - getEasyButtonSize(window).x / 2.0f, window.getSize().y / 2.5f - getEasyButtonSize(window).y };
}

sf::Vector2f DifficultyScene::getMediumButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getEasyButtonPosition(window);
	position.y += getEasyButtonSize(window).y + DIFFICULTSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f DifficultyScene::getDifficultButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getMediumButtonPosition(window);
	position.y += getMediumButtonSize(window).y + DIFFICULTSCENE_SPACE_DISTANCE;
	return position;
}

DifficultyScene::DifficultyScene()
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
	sf::Vector2f easyButtonSize = getEasyButtonSize(window);
	sf::Vector2f mediumButtonSize = getMediumButtonSize(window);
	sf::Vector2f difficultButtonSize = getDifficultButtonSize(window);

	sf::Vector2f easyButtonPosition = getEasyButtonPosition(window);
	sf::Vector2f mediumButtonPosition = getMediumButtonPosition(window);
	sf::Vector2f difficultButtonPosition = getDifficultButtonPosition(window);

	// CONFIGURE
	m_easy.configure(easyButtonPosition, easyButtonSize, "Easy", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "EASY" << std::endl;
		});
	m_medium.configure(mediumButtonPosition, mediumButtonSize, "Medium", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "MEDIUM" << std::endl;
		});
	m_difficult.configure(difficultButtonPosition, difficultButtonSize, "Difficult", FontManager::getInstance()->getFont("SUPERMARIO256"), []()
		{
			std::cout << "DIFFICULT" << std::endl;
		});

	// SET RENDER ORDER
	m_easy.setRenderOrder(10);
	m_easy.setTextViewRenderOrder(20);
	m_medium.setRenderOrder(10);
	m_medium.setTextViewRenderOrder(20);
	m_difficult.setRenderOrder(10);
	m_difficult.setTextViewRenderOrder(20);
}

DifficultyScene::~DifficultyScene()
{
}

void DifficultyScene::update()
{
}

void DifficultyScene::render()
{
}

void DifficultyScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized)
	{
		// ... Finish Later
	}
}
