#pragma once

#include "Scene.hpp"
#include "TextView.hpp"
#include "Button.hpp"
// Include Manager
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"

constexpr float LOGINSCENE_SPACE_DISTANCE = 25;

class LoginScene : public Scene
{
private:
	sf::Vector2f m_getUsernameInputFieldSize(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordInputFieldSize(sf::RenderWindow& window);
	sf::Vector2f m_getConfirmButtonSize(sf::RenderWindow& window);
	sf::Vector2f m_getUsernameTextViewSize(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordTextViewSize(sf::RenderWindow& window);
	sf::Vector2f m_getTitleTextViewSize(sf::RenderWindow& window);

	sf::Vector2f m_getUsernameInputFieldPosition(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordInputFieldPosition(sf::RenderWindow& window);
	sf::Vector2f m_getConfirmButtonPosition(sf::RenderWindow& window);
	sf::Vector2f m_getUsernameTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f m_getPasswordTextViewPosition(sf::RenderWindow& window);
	sf::Vector2f m_getTitleTextViewPosition(sf::RenderWindow& window);

	TextView m_title;
	Button m_confirm;
	//SpriteRenderer m_background;

public:
	LoginScene();
	~LoginScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

