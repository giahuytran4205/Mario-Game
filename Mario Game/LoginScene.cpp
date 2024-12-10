#include "LoginScene.hpp"

sf::Vector2f LoginScene::m_getUsernameInputFieldSize(sf::RenderWindow& window)
{
	return { window.getSize().x / 3.5f, window.getSize().y / 12.0f };
}

sf::Vector2f LoginScene::m_getPasswordInputFieldSize(sf::RenderWindow& window)
{
	return m_getUsernameInputFieldSize(window);
}

sf::Vector2f LoginScene::m_getConfirmButtonSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordInputFieldSize(window);
	size.x = size.x;
	size.y = size.y;
	return size;
}

sf::Vector2f LoginScene::m_getUsernameTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameInputFieldSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::m_getPasswordTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getPasswordInputFieldSize(window);
	return { size.x / 2.0f, size.y };
}

sf::Vector2f LoginScene::m_getTitleTextViewSize(sf::RenderWindow& window)
{
	sf::Vector2f size = m_getUsernameInputFieldSize(window);
	return { size.x * 2, size.y * 2 };
}

// POSITION

sf::Vector2f LoginScene::m_getUsernamePosition(sf::RenderWindow& window)
{
	return { (window.getSize().x - m_getUsernameInputFieldSize(window).x) / 2.0f, window.getSize().y / 2.0f - m_getUsernameInputFieldSize(window).y };
}

sf::Vector2f LoginScene::m_getPasswordPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.y += m_getUsernameInputFieldSize(window).y;
	position.y += LOGINSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f LoginScene::m_getConfirmButtonPosition(sf::RenderWindow& window)
{
	sf::Vector2 position = m_getPasswordInputFieldSize(window);
	position.y += m_getPasswordInputFieldSize(window).y;
	position.y += LOGINSCENE_SPACE_DISTANCE / 2.0f;
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

sf::Vector2f LoginScene::m_getTitleTextViewPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.x += m_getUsernamePosition(window).x / 2.0f - m_getTitleTextViewSize(window).x / 2.0f;
	position.y -= (m_getTitleTextViewSize(window).y + LOGINSCENE_SPACE_DISTANCE);
	return position;
}

LoginScene::LoginScene()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	window.clear(sf::Color::White);

	// SET RENDER WINDOW FOR TEXT VIEW, BUTTON, INPUT FIELD, ...
	//m_title.setRenderWindow(&window);
	//m_confirm.setRenderWindow(&window);

	sf::Vector2f usernameSize = m_getUsernameInputFieldSize(window);
	sf::Vector2f passwordSize = m_getPasswordInputFieldSize(window);
	sf::Vector2f confirmSize = m_getConfirmButtonSize(window);
	sf::Vector2f usernameTextViewSize = m_getUsernameTextViewSize(window);
	sf::Vector2f passwordTextViewSize = m_getPasswordTextViewSize(window);
	sf::Vector2f titleSize = m_getTitleTextViewSize(window);

	sf::Vector2f usernamePosition = m_getUsernamePosition(window);
	sf::Vector2f passwordPosition = m_getPasswordPosition(window);
	sf::Vector2f confirmPosition = m_getConfirmButtonPosition(window);
	sf::Vector2f usernameTextViewPosition = m_getUsernameTextViewPosition(window);
	sf::Vector2f passwordTextViewPosition = m_getPasswordTextViewPosition(window);
	sf::Vector2f titlePosition = m_getTitleTextViewPosition(window);

	//m_title.configure(titlePosition, titleSize, "MARIO GAME", FontManager::getInstance()->getFont("SUPERMARIO256"));
	//m_confirm.configure(confirmPosition, confirmSize, "CONFIRM", FontManager::getInstance()->getFont("ARIAL"), Color::Red, []()
	//	{
	//		std::cout << "CONFIRM BUTTON" << std::endl;
	//	});
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
		// Idea 1: Destroy "this" and add new LoginScene when Resize
		// Idea 2: Reset position & size of all objects in Window
	}
}
