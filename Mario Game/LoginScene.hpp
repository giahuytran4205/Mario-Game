#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include "TextView.hpp"
#include "InputField.hpp"
// Include Manager
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

constexpr float LOGINSCENE_SPACE_DISTANCE = 25;

class LoginScene : public Scene
{
private:
	sf::Vector2f getConfirmButtonSize(sf::RenderWindow& window);
	sf::Vector2f getTitleTextViewSize(sf::RenderWindow& window);
	sf::Vector2f getUsernameTextViewSize(sf::RenderWindow& window);
	sf::Vector2f getPasswordTextViewSize(sf::RenderWindow& window);
	sf::Vector2f getUsernameInputFieldSize(sf::RenderWindow& window);
	sf::Vector2f getPasswordInputFieldSize(sf::RenderWindow& window);

	sf::Vector2f getConfirmButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getTitleTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f getUsernameTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f getPasswordTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f getPasswordInputFieldPosition(sf::RenderWindow& window);
	sf::Vector2f getUsernameInputFieldPosition(sf::RenderWindow& window);

	Button m_confirm;
	TextView m_title;
	TextView m_usernameText;
	TextView m_passwordText;
	InputField m_usernameInput;
	InputField m_passwordInput;
	//SpriteRenderer m_background;

public:
	LoginScene();
	~LoginScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

