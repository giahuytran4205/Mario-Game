#pragma once

#include "GameManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "InputField.hpp"
#include "TextView.hpp"
#include "Enum.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "AccountManager.hpp"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "SFML/Graphics.hpp"

constexpr float SPACE_DISTANCE = 25;

class InputField;
class Button;
class TextView;

class LoginScene : public Scene
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

	void fitBackground(sf::Sprite* sprite, sf::RenderWindow& window);

	TextView* m_titleTextView;
	InputField* m_username;
	InputField* m_password;
	TextView* m_usernameTextView;
	TextView* m_passwordTextView;
	Button* m_confirm;
	SpriteRenderer m_backgroundSprite;

public:
	LoginScene();
	~LoginScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};
