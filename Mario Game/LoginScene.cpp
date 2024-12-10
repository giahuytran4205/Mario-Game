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

// POSITION

sf::Vector2f LoginScene::m_getUsernamePosition(sf::RenderWindow& window)
{
	return { (window.getSize().x - m_getUsernameSize(window).x) / 2.0f, window.getSize().y / 2.0f - m_getUsernameSize(window).y };
}

sf::Vector2f LoginScene::m_getPasswordPosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.y += m_getUsernameSize(window).y;
	position.y += LOGINSCENE_SPACE_DISTANCE;
	return position;
}

sf::Vector2f LoginScene::m_getConfirmPosition(sf::RenderWindow& window)
{
	sf::Vector2 position = m_getPasswordPosition(window);
	position.y += m_getPasswordSize(window).y;
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

sf::Vector2f LoginScene::m_getTitlePosition(sf::RenderWindow& window)
{
	sf::Vector2f position = m_getUsernamePosition(window);
	position.x += m_getUsernamePosition(window).x / 2.0f - m_getTitleSize(window).x / 2.0f;
	position.y -= (m_getTitleSize(window).y + LOGINSCENE_SPACE_DISTANCE);
	return position;
}

LoginScene::LoginScene() :
	m_title(this)
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	sf::Vector2f usernameSize = m_getUsernameSize(window);
	sf::Vector2f passwordSize = m_getPasswordSize(window);
	sf::Vector2f confirmSize = m_getConfirmSize(window);
	sf::Vector2f usernameTextViewSize = m_getUsernameTextViewSize(window);
	sf::Vector2f passwordTextViewSize = m_getPasswordTextViewSize(window);
	sf::Vector2f titleSize = m_getTitleSize(window);

	sf::Vector2f usernamePosition = m_getUsernamePosition(window);
	sf::Vector2f passwordPosition = m_getPasswordPosition(window);
	sf::Vector2f confirmPosition = m_getConfirmPosition(window);
	sf::Vector2f usernameTextViewPosition = m_getUsernameTextViewPosition(window);
	sf::Vector2f passwordTextViewPosition = m_getPasswordTextViewPosition(window);
	sf::Vector2f titlePosition = m_getTitlePosition(window);


	m_title.configure(FRect(titlePosition.x, titlePosition.y, titleSize.x, titleSize.y), "MARIO GAME", FontManager::getInstance()->getFont("SUPERMARIO256"));
	m_title.setFillColor(sf::Color::White);
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
