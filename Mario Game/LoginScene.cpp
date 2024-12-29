#include "LoginScene.hpp"
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"
#include "MapSelectionScene.hpp"

const float WIDTH_RATIO = 10.0f;
const float HEIGHT_RATIO = 10.0f;

sf::Vector2f LoginScene::getUsernameInputFieldSize()
{
	return getConfirmButtonSize();
}

sf::Vector2f LoginScene::getPasswordInputFieldSize()
{
	return getConfirmButtonSize();
}

sf::Vector2f LoginScene::getConfirmButtonSize()
{
	sf::Vector2f size = GameManager::getInstance()->getView().getSize();
	size.x = size.x / WIDTH_RATIO * 3.5f;
	size.y = size.y / HEIGHT_RATIO;
	return size;
}

sf::Vector2f LoginScene::getUsernameTextViewSize()
{
	sf::Vector2f size = getUsernameInputFieldSize();
	size.x /= 2.0f;
	return size;
}

sf::Vector2f LoginScene::getPasswordTextViewSize()
{
	return getUsernameTextViewSize();
}

sf::Vector2f LoginScene::getTitleTextViewSize()
{
	sf::Vector2f size = GameManager::getInstance()->getView().getSize();
	size.x = size.x / WIDTH_RATIO * 4.5f;
	size.y = size.y / HEIGHT_RATIO * 2.0f;
	return size;
}

// POSITION

sf::Vector2f LoginScene::getUsernameInputFieldPosition()
{
	sf::Vector2f position = getPasswordInputFieldPosition();
	position.y -= getPasswordInputFieldSize().y + 5.0f;
	return position;
}

sf::Vector2f LoginScene::getPasswordInputFieldPosition()
{
	sf::Vector2f position = getConfirmButtonPosition();
	position.x -= getPasswordInputFieldSize().x / 2.0f;
	position.y -= getConfirmButtonSize().y / 2.0f + getPasswordInputFieldSize().y + 5.0f;
	return position;
}

sf::Vector2f LoginScene::getConfirmButtonPosition()
{
	sf::View view = GameManager::getInstance()->getView();
	return sf::Vector2f(view.getSize().x / 2.0f, view.getSize().y / HEIGHT_RATIO * 7.0f);
}

sf::Vector2f LoginScene::getUsernameTextViewPosition()
{
	sf::Vector2f position = getUsernameInputFieldPosition();
	position.x -= getUsernameTextViewSize().x / 2.0f;
	position.y += getUsernameTextViewSize().y / 2.0f;
	return position;
}

sf::Vector2f LoginScene::getPasswordTextViewPosition()
{
	sf::Vector2f position = getPasswordInputFieldPosition();
	position.x -= getPasswordTextViewSize().x / 2.0f;
	position.y += getPasswordTextViewSize().y / 2.0f;
	return position;
}

sf::Vector2f LoginScene::getTitleTextViewPosition()
{
	sf::Vector2f position = getUsernameInputFieldPosition();
	position.x += getUsernameInputFieldSize().x / 2.0f;
	position.y -= getTitleTextViewSize().y / 2.0f + 10.0f;
	return position;
}

LoginScene::LoginScene() :
	m_usernameInput(getUsernameInputFieldPosition(), getUsernameInputFieldSize(), FontManager::getInstance()->getFont("ARIAL"), this),
	m_passwordInput(getPasswordInputFieldPosition(), getPasswordInputFieldSize(), FontManager::getInstance()->getFont("ARIAL"), this)
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();

	// SET VIEW;
	sf::View& view = GameManager::getInstance()->getView();
	view.setCenter(view.getSize() / 2.0f);

	// SET BACKGROUND
	m_background.setTexture(TextureManager::getTexture("Resources/Background/MarioBros-Background.png"));
	m_background.scale(view.getSize().x / m_background.getGlobalBounds().width, view.getSize().y / m_background.getGlobalBounds().height);

	m_confirm.setParent(this);
	m_confirm.configure(getConfirmButtonSize(), getConfirmButtonPosition(), "Confirm", FontManager::getInstance()->getFont("ARIAL"));
	m_confirm.getComponent<Transform2D>().setRect(getConfirmButtonPosition().x, getConfirmButtonPosition().y, getConfirmButtonSize().x, getConfirmButtonSize().y);
	m_confirm.getText().setCharacterSize(12);
	m_confirm.setAction([this, sceneManager = SceneManager::getInstance()]() {
			std::cout << "LOGIN::Confirm Button Clicked\n";
			bool isPasswordCorrect = false;
			if (m_usernameInput.getContent() == "a" && m_passwordInput.getContent() == "1")
			{
				std::cout << "Login Successfully" << std::endl;
				isPasswordCorrect = true;
			}
			else
			{
				std::cout << "Login Falied" << std::endl;
			}
			m_usernameInput.clearContent();
			m_passwordInput.clearContent();

			if (isPasswordCorrect)
			{
				/*sceneManager->setCurrentScene<MapSelectionScene>();*/
			}
		});

	m_title.setParent(this);
	m_title.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_title.setCharacterSize(18);
	m_title.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_title.getComponent<Transform2D>().setPosition(getTitleTextViewPosition());
	m_title.getComponent<Transform2D>().setSize(getTitleTextViewSize());
	m_title.setString("SUPER MARIO BROS");

	m_usernameText.setParent(this);
	m_usernameText.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_usernameText.setCharacterSize(12);
	m_usernameText.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_usernameText.getComponent<Transform2D>().setPosition(getUsernameTextViewPosition());
	m_usernameText.getComponent<Transform2D>().setSize(getUsernameTextViewSize());
	m_usernameText.setString("Username");

	m_passwordText.setParent(this);
	m_passwordText.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_passwordText.setCharacterSize(12);
	m_passwordText.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_passwordText.getComponent<Transform2D>().setPosition(getPasswordTextViewPosition());
	m_passwordText.getComponent<Transform2D>().setSize(getPasswordTextViewSize());
	m_passwordText.setString("Password");
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