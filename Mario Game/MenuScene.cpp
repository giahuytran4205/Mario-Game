#include "MenuScene.hpp"

// SIZE

sf::Vector2f MenuScene::m_getPlayerNameLabelSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 4.0f, window.getSize().y / 8.0f };
}

sf::Vector2f MenuScene::m_getPlayerNameTextSize(sf::RenderWindow& window)
{
	sf::Vector2f playerNameLabelSize = m_getPlayerNameLabelSize(window);
	return { playerNameLabelSize.x * 1.5f, playerNameLabelSize.y };
}

sf::Vector2f MenuScene::m_getMaxScoreLabelSize(sf::RenderWindow& window)
{
	return m_getPlayerNameLabelSize(window);
}

sf::Vector2f MenuScene::m_getMaxScoreTextSize(sf::RenderWindow& window)
{
	sf::Vector2f maxScoreLabelSize = m_getMaxScoreLabelSize(window);
	return { maxScoreLabelSize.x * 1.5f, maxScoreLabelSize.y };
}

sf::Vector2f MenuScene::m_getBackButtonSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f, window.getSize().y / 8.0f };
}

sf::Vector2f MenuScene::m_getNextButtonSize(sf::RenderWindow& window)
{
	return m_getBackButtonSize(window);
}

// POSITION

sf::Vector2f MenuScene::m_getPlayerNameLabelPosition(sf::RenderWindow& window)
{
	return { window.getSize().x / 6.0f, window.getSize().y / 6.0f };
}

sf::Vector2f MenuScene::m_getPlayerNameTextPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getPlayerNameLabelPosition(window);
	sf::Vector2f playerNameLabelSize = m_getPlayerNameLabelSize(window);
	position.x += playerNameLabelSize.x;
	return position;
}

sf::Vector2f MenuScene::m_getMaxScoreLabelPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getPlayerNameLabelPosition(window);
	sf::Vector2f playerNameLabelSize = m_getPlayerNameLabelSize(window);
	position.y += playerNameLabelSize.y + SPACE_DISTANCE;
	return position;
}

sf::Vector2f MenuScene::m_getMaxScoreTextPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getMaxScoreLabelPosition(window);
	sf::Vector2f maxScoreLabelSize = m_getMaxScoreLabelSize(window);
	position.x += maxScoreLabelSize.x;
	return position;
}

sf::Vector2f MenuScene::m_getBackButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f backButtonSize = m_getBackButtonSize(window);
	return { window.getSize().x - backButtonSize.x, 0 };
}

sf::Vector2f MenuScene::m_getNextButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2f nextButtonSize = m_getNextButtonSize(window);
	return { window.getSize().x - nextButtonSize.x, window.getSize().y - nextButtonSize.y };
}

void MenuScene::fitBackground(sf::Sprite* sprite, sf::RenderWindow& window)
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

MenuScene::MenuScene(Account* account)
{
	m_account = account;

	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	// LOAD BACKGROUND
	m_backgroundSprite.setTexture(TextureManager::m_instance->m_background[BackgroundType::LOGINSTATE_BACKGROUND]);
	this->fitBackground(&m_backgroundSprite, window);

	// GET ALL OBJECT's SIZES
	sf::Vector2f playerNameLabelSize = m_getPlayerNameLabelSize(window);
	sf::Vector2f playerNameTextSize = m_getPlayerNameTextSize(window);
	sf::Vector2f maxScoreLabelSize = m_getMaxScoreLabelSize(window);
	sf::Vector2f maxScoreTextSize = m_getMaxScoreTextSize(window);
	sf::Vector2f backButtonSize = m_getBackButtonSize(window);
	sf::Vector2f nextButtonSize = m_getNextButtonSize(window);

	// GET ALL OBJECT's POSITIONS
	sf::Vector2f playerNameLabelPosition = m_getPlayerNameLabelPosition(window);
	sf::Vector2f playerNameTextPosition = m_getPlayerNameTextPosition(window);
	sf::Vector2f maxScoreLabelPosition = m_getMaxScoreLabelPosition(window);
	sf::Vector2f maxScoreTextPosition = m_getMaxScoreTextPosition(window);
	sf::Vector2f backButtonPosition = m_getBackButtonPosition(window);
	sf::Vector2f nextButtonPosition = m_getNextButtonPosition(window);

	m_playerNameLabel = new TextView(
		this,
		{ playerNameLabelPosition.x, playerNameLabelPosition.y, playerNameLabelSize.x, playerNameLabelSize.y },
		"PLAYER : ",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(playerNameLabelSize.y / 2.5)
	);

	m_playerNameText = new TextView(
		this,
		{ playerNameTextPosition.x, playerNameTextPosition.y, playerNameTextSize.x, playerNameTextSize.y },
		toUpperCase(m_account->getUsername()),
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(playerNameTextSize.y / 2.5)
	);

	m_maxScoreLabel = new TextView(
		this,
		{ maxScoreLabelPosition.x, maxScoreLabelPosition.y, maxScoreLabelSize.x, maxScoreLabelSize.y },
		"MAX SCORE: ",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(maxScoreLabelSize.y / 2.5)
	);

	m_maxScoreText = new TextView(
		this,
		{ maxScoreTextPosition.x, maxScoreTextPosition.y, maxScoreTextSize.x, maxScoreTextSize.y },
		toUpperCase(std::to_string(m_account->getMaxScore())),
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(maxScoreTextSize.y / 2.5)
	);

	m_backButton = new Button(
		this,
		window,
		backButtonPosition.x, backButtonPosition.y, 
		backButtonSize.x, backButtonSize.y,
		"BACK",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[]()
		{
			std::cout << "Back Button of MenuScene is Entered!" << std::endl;
		}
	);

	m_nextButton = new Button(
		this,
		window,
		nextButtonPosition.x, nextButtonPosition.y,
		nextButtonSize.x, nextButtonSize.y,
		"NEXT",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[]()
		{
			std::cout << "Next Button of MenuScene is Entered!" << std::endl;
		}
	);
}

MenuScene::~MenuScene()
{
	delete m_account;
	delete m_playerNameLabel;
	delete m_playerNameText;
	delete m_maxScoreLabel;
	delete m_maxScoreText;
	delete m_backButton;
	delete m_nextButton;
}

void MenuScene::update()
{
}

void MenuScene::render()
{
}

void MenuScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized) {
		// ... Finish Later
		// Idea 1: Destroy "this" and add new LoginScene when Resize
		// Idea 2: Reset position & size of all objects in Window
	}
}
