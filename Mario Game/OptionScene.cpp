#include "OptionScene.hpp"

sf::Vector2f OptionScene::m_getThemeVolumeSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f * 3.0f , 20.0f};
}

sf::Vector2f OptionScene::m_getTotalVolumeSize(sf::RenderWindow& window)
{
	return m_getThemeVolumeSize(window);
}

sf::Vector2f OptionScene::m_getEffectVolumeSize(sf::RenderWindow& window)
{
	return m_getThemeVolumeSize(window);
}

sf::Vector2f OptionScene::m_getContinueButtonSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f, window.getSize().y / 8.0f };
}

sf::Vector2f OptionScene::m_getHomeButtonSize(sf::RenderWindow& window)
{
	return m_getContinueButtonSize(window);
}

sf::Vector2f OptionScene::m_getExitButtonSize(sf::RenderWindow& window)
{
	return m_getContinueButtonSize(window);
}

sf::Vector2f OptionScene::m_getThemeVolumePostion(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f * 2.0f, window.getSize().y / 8.0f * 2.0f };
}

sf::Vector2f OptionScene::m_getTotalVolumePostion(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f * 2.0f, window.getSize().y / 8.0f * 4.0f };
}

sf::Vector2f OptionScene::m_getEffectVolumePostion(sf::RenderWindow& window)
{
	return { window.getSize().x / 7.0f * 2.0f, window.getSize().y / 8.0f * 6.0f };
}

sf::Vector2f OptionScene::m_getContinueButtonPostion(sf::RenderWindow& window)
{
	return 
	{ 
		window.getSize().x / 2.0f - m_getContinueButtonSize(window).x / 2.0f,
		window.getSize().y / 8.0f * 7.0f
	};
}

sf::Vector2f OptionScene::m_getHomeButtonPostion(sf::RenderWindow& window)
{
	return { 0.0f, 0.0f };
}

sf::Vector2f OptionScene::m_getExitButtonPostion(sf::RenderWindow& window)
{
	return {window.getSize().x - m_getExitButtonSize(window).x, 0};
}

OptionScene::OptionScene()
	//m_totalVolume(this),
	//m_themeVolume(this),
	//m_effectVolume(this)
	//m_continue(this),
	//m_exit(this),
	//m_home(this)
{

	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	// LOAD BACKGROUND
	m_background.setTexture(TextureManager::m_instance->m_background[BackgroundType::LOGINSTATE_BACKGROUND]);
	this->fitBackground(&m_background, window);

	// GET SIZE ACCORDING TO WINDOW
	sf::Vector2f themeVolumeSize = m_getThemeVolumeSize(window);
	sf::Vector2f totalVolumeSize = m_getTotalVolumeSize(window);
	sf::Vector2f effectVolumeSize = m_getEffectVolumeSize(window);
	sf::Vector2f continueButtonSize = m_getContinueButtonSize(window);
	sf::Vector2f homeButtonSize = m_getHomeButtonSize(window);
	sf::Vector2f exitButtonSize = m_getExitButtonSize(window);

	// GET POSITION
	sf::Vector2f themeVolumePosition = m_getThemeVolumePostion(window);
	sf::Vector2f totalVolumePosition = m_getTotalVolumePostion(window);
	sf::Vector2f effectVolumePosition = m_getEffectVolumePostion(window);
	sf::Vector2f continueButtonPosition = m_getContinueButtonPostion(window);
	sf::Vector2f homeButtonPosition = m_getHomeButtonPostion(window);
	sf::Vector2f exitButtonPosition = m_getExitButtonPostion(window);

	m_continue = new Button(
		this,
		window,
		continueButtonPosition.x, continueButtonPosition.y,
		continueButtonSize.x, continueButtonSize.y,
		"Continue",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[this, sceneManager = SceneManager::getInstance()]()
		{
			std::cout << "Confirm Button";
		}
	);

	m_exit = new Button(
		this,
		window,
		exitButtonPosition.x, exitButtonPosition.y,
		exitButtonSize.x, exitButtonSize.y,
		"Exit",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[this, sceneManager = SceneManager::getInstance()]()
		{
			std::cout << "Exit Button";
		}
	);

	m_home = new Button(
		this,
		window,
		homeButtonPosition.x, homeButtonPosition.y,
		homeButtonSize.x, homeButtonSize.y,
		"Home",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[this, sceneManager = SceneManager::getInstance()]()
		{
			std::cout << "Confirm Button";
		}
	);

	m_totalVolume = new Slider<float>(
		window,
		0.0f, 100.0f, 50.0f,
		totalVolumePosition,
		this
	);

	m_themeVolume = new Slider<float>(
		window,
		0.0f, 100.0f, 50.0f,
		themeVolumePosition,
		this
	);

	m_effectVolume = new Slider<float>(
		window,
		0.0f, 100.0f, 50.0f,
		effectVolumePosition,
		this
	);

	//// SET POSITION
	//m_themeVolume.setSize(themeVolumeSize);
	//m_totalVolume.setSize(totalVolumeSize);
	//m_effectVolume.setSize(effectVolumeSize);
	//m_continue->setSize(continueButtonSize);
	//m_home->setSize(homeButtonSize);
	//m_exit->setSize(exitButtonSize);

	//// SET POSITION
	//m_themeVolume.setPosition(themeVolumePosition);
	//m_totalVolume.setPosition(totalVolumeSize);
	//m_effectVolume.setPosition(effectVolumeSize);
	//m_continue->setPosition(continueButtonPosition);
	//m_home->setPosition(homeButtonPosition);
	//m_exit->setPosition(exitButtonPosition);

	//// SET BUTTON TEXT
	//m_continue->setLabelContent("CONTINUE");
	//m_home->setLabelContent("HOME");
	//m_exit->setLabelContent("EXIT");

	//// SET FONT
	//m_continue->setTextFont(FontManager::m_instance->m_font[FontType::ARIAL]);
	//m_home->setTextFont(FontManager::m_instance->m_font[FontType::ARIAL]);
	//m_exit->setTextFont(FontManager::m_instance->m_font[FontType::ARIAL]);

	//// SCALE BUTTON's TEXT 
	//m_continue->setScaleTextSize(0.5f);
	//m_home->setScaleTextSize(0.5f);
	//m_exit->setScaleTextSize(0.5f);
}

OptionScene::~OptionScene()
{
	delete m_continue;
	delete m_home;
	delete m_exit;
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
