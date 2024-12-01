#pragma once

#include "GameManager.hpp"
#include "State.hpp"
#include "Button.hpp"
#include "InputField.hpp"
#include "Enum.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "SFML/Graphics.hpp"

#include <vector>

class Button;
class InputField;

constexpr float SPACE_DISTANCE = 25;

class LoginState : public State
{
private:
	sf::Vector2f m_getUsernameSize(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordSize(sf::RenderWindow& window);
	sf::Vector2f m_getConfirmSize(sf::RenderWindow& window);
	sf::Vector2f m_getUsernameTextViewSize(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordTextViewSize(sf::RenderWindow& window);
	sf::Vector2f m_getTitleSize(sf::RenderWindow& window);

	sf::Vector2f m_getUsernamePosition(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordPosition(sf::RenderWindow& window);
	sf::Vector2f m_getConfirmPosition(sf::RenderWindow& window);
	sf::Vector2f m_getUsernameTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f m_getTitlePosition(sf::RenderWindow& window);

	TextView* m_titleTextView;
	InputField* m_username;
	InputField* m_password;
	TextView* m_usernameTextView;
	TextView* m_passwordTextView;
	Button* m_confirm;
	sf::Sprite m_backgroundSprite;

public:
	LoginState();
	~LoginState();

	void init() override;
	void handleEvents() override;
	void update(float dT) override;
	void render(float dT) override;
};
