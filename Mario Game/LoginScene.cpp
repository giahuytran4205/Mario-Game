#include "LoginScene.hpp"
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

sf::Vector2f LoginScene::getUsernameInputFieldSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 3.5f, window.getSize().y / 12.0f };
}

sf::Vector2f LoginScene::getPasswordInputFieldSize(sf::RenderWindow& window)
{
	return getUsernameInputFieldSize(window);
}

sf::Vector2f LoginScene::getConfirmButtonSize(sf::RenderWindow& window)
{
	sf::Vector2f size = getPasswordInputFieldSize(window);
	size.x = size.x;
	size.y = size.y;
	return size;
}

sf::Vector2f LoginScene::getUsernameTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = getUsernameInputFieldSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::getPasswordTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = getPasswordInputFieldSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::getTitleTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = getUsernameInputFieldSize(window);
	return { size.x * 2, size.y * 2 };
}

// POSITION

sf::Vector2f LoginScene::getUsernameInputFieldPosition(sf::RenderWindow& window)
{
	return { (window.getSize().x - getUsernameInputFieldSize(window).x) / 2.0f, window.getSize().y / 2.0f - getUsernameInputFieldSize(window).y };
}

sf::Vector2f LoginScene::getPasswordInputFieldPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getUsernameInputFieldPosition(window);
	position.y += getUsernameInputFieldSize(window).y;
	position.y += LOGINSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f LoginScene::getConfirmButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2 position = getPasswordInputFieldPosition(window);
	position.y += getPasswordInputFieldSize(window).y;
	position.y += LOGINSCENE_SPACE_DISTANCE / 2.0f;
	return position;
}

sf::Vector2f LoginScene::getUsernameTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getUsernameInputFieldPosition(window);
	sf::Vector2f size = getUsernameTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginScene::getPasswordTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getPasswordInputFieldPosition(window);
	sf::Vector2f size = getPasswordTextViewSize(window);
	return { position.x - size.x, position.y };
}

sf::Vector2f LoginScene::getTitleTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = getUsernameInputFieldPosition(window);
	position.x += getUsernameInputFieldPosition(window).x / 2.0f - getTitleTextViewSize(window).x / 2.0f;
	position.y -= (getTitleTextViewSize(window).y + LOGINSCENE_SPACE_DISTANCE);
	return position;
}

LoginScene::LoginScene()
	:
	m_confirm(this),
	m_title(this),
	m_usernameText(this),
	m_passwordText(this),
	m_usernameInput(this),
	m_passwordInput(this),
	m_background(this)
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
	sf::Vector2f usernameInputFieldSize = this->getUsernameInputFieldSize(window);
	sf::Vector2f passwordInputFieldSize = this->getPasswordInputFieldSize(window);
	sf::Vector2f usernameTextViewSize = this->getUsernameTextViewSize(window);
	sf::Vector2f passwordTextViewSize = this->getPasswordTextViewSize(window);
	sf::Vector2f confirmButtonSize = this->getConfirmButtonSize(window);
	sf::Vector2f titleTextViewSize = this->getTitleTextViewSize(window);

	sf::Vector2f usernameInputFieldPosition = this->getUsernameInputFieldPosition(window);
	sf::Vector2f passwordInputFieldPosition = this->getPasswordInputFieldPosition(window);
	sf::Vector2f usernameTextViewPosition = this->getUsernameTextViewPosition(window);
	sf::Vector2f passwordTextViewPosition = this->getPasswordTextViewPosition(window);
	sf::Vector2f confirmButtonPosition = this->getConfirmButtonPosition(window);
	sf::Vector2f titleTextViewPosition = this->getTitleTextViewPosition(window);

	// CONFIGURE
	m_usernameText.configure(usernameTextViewPosition, usernameTextViewSize, "Username", FontManager::getInstance()->getFont("ARIAL"));
	m_passwordText.configure(passwordTextViewPosition, passwordTextViewSize, "Password", FontManager::getInstance()->getFont("ARIAL"));
	m_usernameInput.configure(usernameInputFieldPosition, usernameInputFieldSize, FontManager::getInstance()->getFont("ARIAL"));
	m_passwordInput.configure(passwordInputFieldPosition, passwordInputFieldSize, FontManager::getInstance()->getFont("ARIAL"));
	m_title.configure(titleTextViewPosition, titleTextViewSize, "MARIO GAME", FontManager::getInstance()->getFont("SUPERMARIO256"));
	m_confirm.configure(confirmButtonPosition, confirmButtonSize, "CONFIRM", FontManager::getInstance()->getFont("ARIAL"), []()
		{
			std::cout << "CONFIRM BUTTON" << std::endl;
		});

	// SET RENDER ORDER
	m_usernameText.setRenderOrder(10);
	m_passwordText.setRenderOrder(10);
	m_usernameInput.setRenderOrder(10);
	m_passwordInput.setRenderOrder(10);
	m_title.setRenderOrder(10);
	m_confirm.setRenderOrder(10);
	m_confirm.setTextViewRenderOrder(20);
}

LoginScene::~LoginScene()
{
}

void LoginScene::update()
{
}

void LoginScene::render()
{
}

void LoginScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized)
	{
		// ... Finish Later
	}
}
