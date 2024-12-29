#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include "TextView.hpp"
#include "InputField.hpp"

constexpr float LOGINSCENE_SPACE_DISTANCE = 25.0f;

class LoginScene : public Scene
{
private:
	sf::Vector2f getConfirmButtonSize();
	sf::Vector2f getTitleTextViewSize();
	sf::Vector2f getUsernameTextViewSize();
	sf::Vector2f getPasswordTextViewSize();
	sf::Vector2f getUsernameInputFieldSize();
	sf::Vector2f getPasswordInputFieldSize();

	sf::Vector2f getConfirmButtonPosition();
	sf::Vector2f getTitleTextViewPosition();
	sf::Vector2f getUsernameTextViewPosition();
	sf::Vector2f getPasswordTextViewPosition();
	sf::Vector2f getPasswordInputFieldPosition();
	sf::Vector2f getUsernameInputFieldPosition();

	Button m_confirm;
	TextView m_title;
	TextView m_usernameText;
	TextView m_passwordText;
	InputField m_usernameInput;
	InputField m_passwordInput;
	SpriteRenderer m_background;

public:
	LoginScene();
	~LoginScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};