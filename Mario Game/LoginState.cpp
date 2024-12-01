#include "LoginState.hpp"

sf::Vector2f LoginState::m_getUsernameSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 3.5f, window.getSize().y / 12.0f };
}

sf::Vector2f LoginState::m_getPasswordSize(sf::RenderWindow& window)
{
	return m_getUsernameSize(window);
}

sf::Vector2f LoginState::m_getConfirmSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordSize(window);
	size.x = size.x;
	size.y = size.y;
	return size;
}

sf::Vector2f LoginState::m_getUsernameTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginState::m_getPasswordTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginState::m_getTitleSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameSize(window);
	return { size.x * 2, size.y * 2 };
}

sf::Vector2f LoginState::m_getUsernamePosition(sf::RenderWindow& window)
{
	return { (window.getSize().x - m_getUsernameSize(window).x) / 2.0f, window.getSize().y / 2.0f - m_getUsernameSize(window).y };
}

sf::Vector2f LoginState::m_getPasswordPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.y += m_getUsernameSize(window).y;
	position.y += SPACE_DISTANCE;
	return position;
}

sf::Vector2f LoginState::m_getConfirmPosition(sf::RenderWindow& window)
{
	sf::Vector2 position = m_getPasswordPosition(window);
	position.y += m_getPasswordSize(window).y;
	position.y += SPACE_DISTANCE / 2.0f;
	return position;
}

sf::Vector2f LoginState::m_getUsernameTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	sf::Vector2f size = m_getUsernameTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginState::m_getPasswordTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getPasswordPosition(window);
	sf::Vector2f size = m_getPasswordTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginState::m_getTitlePosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.x += m_getUsernamePosition(window).x / 2.0f - m_getTitleSize(window).x / 2.0f;
	position.y -= (m_getTitleSize(window).y + SPACE_DISTANCE);
	return position;
}

LoginState::LoginState()
{
	m_titleTextView = nullptr;
	m_username = nullptr;
	m_password = nullptr;
	m_usernameTextView = nullptr;
	m_passwordTextView = nullptr;
	m_confirm = nullptr;
}

LoginState::~LoginState()
{
	delete m_titleTextView;
	delete m_username;
	delete m_password;
	delete m_usernameTextView;
	delete m_passwordTextView;
	delete m_confirm;
}

void LoginState::init()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();

	m_backgroundSprite.setTexture(TextureManager::m_instance->m_background[BackgroundType::LOGINSTATE_BACKGROUND]);
	fitBackground(m_backgroundSprite, window);

	sf::Vector2f usernameSize = m_getUsernameSize(window);
	sf::Vector2f passwordSize = m_getPasswordSize(window);
	sf::Vector2f confirmSize = m_getConfirmSize(window);

	m_username = new InputField(
		window,
		0, 0,
		usernameSize.x, usernameSize.y,
		FontManager::m_instance->m_font[FontType::ARIAL]
	);

	m_password = new InputField(
		window,
		0, 0,
		passwordSize.x, passwordSize.y,
		FontManager::m_instance->m_font[FontType::ARIAL]
	);

	m_confirm = new Button(
		window,
		0, 0,
		confirmSize.x, confirmSize.y,
		"Confirm",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		[this]()
		{
			if (m_username->getContent() == "a" && m_password->getContent() == "1")
			{
				std::cout << "Login Success" << std::endl;
			}
			else
			{
				std::cout << "Login Failed" << std::endl;
			}
			m_username->clearContent();
			m_password->clearContent();
		},
		nullptr
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
		{ usernameTextViewPosition.x, usernameTextViewPosition.y, usernameTextViewSize.x, usernameTextViewSize.y },
		"Username",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(usernameTextViewSize.y / 2.5)
	);

	m_passwordTextView = new TextView(
		{ passwordTextViewPosition.x, passwordTextViewPosition.y, passwordTextViewSize.x, passwordTextViewSize.y },
		"Password",
		FontManager::m_instance->m_font[FontType::ARIAL],
		sf::Color::Black,
		static_cast<unsigned int>(passwordTextViewSize.y / 2.5)
	);


	m_titleTextView = new TextView(
		{ titlePosition.x, titlePosition.y, titleSize.x, titleSize.y },
		"SUPER MARIO BROS",
		FontManager::m_instance->m_font[FontType::SUPERMARIO256],
		sf::Color::Black,
		static_cast<unsigned int>(titleSize.y / 2)
	);
}

void LoginState::handleEvents()
{
	sf::Event event;
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		m_username->handleEvent(event);
		m_password->handleEvent(event);
		m_confirm->handleEvent(event);
	}
}

void LoginState::update(float dT)
{
}

void LoginState::render(float dT)
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	window.clear();

	window.draw(m_backgroundSprite);

	m_username->draw(window);
	m_password->draw(window);
	m_confirm->draw(window);
	window.draw(m_usernameTextView->getText());
	window.draw(m_passwordTextView->getText());
	window.draw(m_titleTextView->getText());

	window.display();
}