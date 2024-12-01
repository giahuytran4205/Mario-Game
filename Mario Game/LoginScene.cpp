#include "LoginScene.hpp"

sf::Vector2f LoginScene::m_getUsernameSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 3.5f, window.getSize().y / 12.0f };
}

sf::Vector2f LoginScene::m_getPasswordSize(sf::RenderWindow& window)
{
	return m_getUsernameSize(window);
}

sf::Vector2f LoginScene::m_getConfirmSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordSize(window);
	size.x = size.x;
	size.y = size.y;
	return size;
}

sf::Vector2f LoginScene::m_getUsernameTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::m_getPasswordTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::m_getTitleSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameSize(window);
	return { size.x * 2, size.y * 2 };
}

sf::Vector2f LoginScene::m_getUsernamePosition(sf::RenderWindow& window)
{
	return { (window.getSize().x - m_getUsernameSize(window).x) / 2.0f, window.getSize().y / 2.0f - m_getUsernameSize(window).y };
}

sf::Vector2f LoginScene::m_getPasswordPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.y += m_getUsernameSize(window).y;
	position.y += SPACE_DISTANCE;
	return position;
}

sf::Vector2f LoginScene::m_getConfirmPosition(sf::RenderWindow& window)
{
	sf::Vector2 position = m_getPasswordPosition(window);
	position.y += m_getPasswordSize(window).y;
	position.y += SPACE_DISTANCE / 2.0f;
	return position;
}

sf::Vector2f LoginScene::m_getUsernameTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	sf::Vector2f size = m_getUsernameTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginScene::m_getPasswordTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getPasswordPosition(window);
	sf::Vector2f size = m_getPasswordTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginScene::m_getTitlePosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.x += m_getUsernamePosition(window).x / 2.0f - m_getTitleSize(window).x / 2.0f;
	position.y -= (m_getTitleSize(window).y + SPACE_DISTANCE);
	return position;
}

void LoginScene::fitBackground(sf::Sprite* sprite, sf::RenderWindow& window)
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

LoginScene::LoginScene()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();

	m_backgroundSprite.setTexture(TextureManager::m_instance->m_background[BackgroundType::LOGINSTATE_BACKGROUND]);
	this->fitBackground(&m_backgroundSprite, window);

	sf::Vector2f usernameSize = m_getUsernameSize(window);
	sf::Vector2f passwordSize = m_getPasswordSize(window);
	sf::Vector2f confirmSize = m_getConfirmSize(window);

	m_username = new InputField(
		this,
		window,
		0, 0,
		usernameSize.x, usernameSize.y,
		FontManager::m_instance->m_font[FontType::ARIAL]
	);

	m_password = new InputField(
		this,
		window,
		0, 0,
		passwordSize.x, passwordSize.y,
		FontManager::m_instance->m_font[FontType::ARIAL]
	);

	m_confirm = new Button(
		this,
		window,
		0, 0,
		confirmSize.x, confirmSize.y,
		"Confirm",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[this, sceneManager = SceneManager::getInstance()]()
		{
			bool isPasswordCorrect = false;
			Account* account = nullptr;
			if (AccountManager::getInstance()->isPasswordCorrect(m_username->getContent(), m_password->getContent(), account))
			{
				std::cout << "Login Successfully" << std::endl;
				isPasswordCorrect = true;
			}
			else
			{
				std::cout << "Login Falied" << std::endl;
			}
			m_username->clearContent();
			m_password->clearContent();

			if (isPasswordCorrect)
			{
				sceneManager->setCurrentScene<GameScene>();
			}
		}
	);

	sf::Vector2f usernamePosition = m_getUsernamePosition(window);
	sf::Vector2f passwordPosition = m_getPasswordPosition(window);
	sf::Vector2f confirmPosition = m_getConfirmPosition(window);
	sf::Vector2f usernameTextViewPosition = m_getUsernameTextViewPosition(window);
	sf::Vector2f passwordTextViewPosition = m_getPasswordTextViewPosition(window);
	sf::Vector2f titlePosition = m_getTitlePosition(window);

	sf::Vector2f usernameTextViewSize = m_getUsernameTextViewSize(window);
	sf::Vector2f passwordTextViewSize = m_getPasswordTextViewSize(window);
	sf::Vector2f titleSize = m_getTitleSize(window);

	m_username->setPosition(usernamePosition.x, usernamePosition.y);
	m_password->setPosition(passwordPosition.x, passwordPosition.y);
	m_confirm->setPosition(confirmPosition.x, confirmPosition.y);

	m_usernameTextView = new TextView(
		this,
		{ usernameTextViewPosition.x, usernameTextViewPosition.y, usernameTextViewSize.x, usernameTextViewSize.y },
		"Username",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(usernameTextViewSize.y / 2.5)
	);

	m_passwordTextView = new TextView(
		this,
		{ passwordTextViewPosition.x, passwordTextViewPosition.y, passwordTextViewSize.x, passwordTextViewSize.y },
		"Password",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(passwordTextViewSize.y / 2.5)
	);


	m_titleTextView = new TextView(
		this,
		{ titlePosition.x, titlePosition.y, titleSize.x, titleSize.y },
		"SUPER MARIO BROS",
		FontManager::m_instance->m_font[FontType::SUPERMARIO256],
		sf::Color::Black,
		static_cast<unsigned int>(titleSize.y / 2)
	);

	View& view = GameManager::getInstance()->getView();
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));

	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);
}

LoginScene::~LoginScene()
{
	delete m_titleTextView;
	delete m_username;
	delete m_password;
	delete m_usernameTextView;
	delete m_passwordTextView;
	delete m_confirm;
}

void LoginScene::update()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();
	view.setSize(window.getSize().x, window.getSize().y);
	window.setView(view);
}

void LoginScene::render()
{
}

void LoginScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized) {
		// ... Finish Later
		// Idea 1: Destroy "this" and add new LoginScene when Resize
		// Idea 2: Reset position & size of all objects in Window
	}
}