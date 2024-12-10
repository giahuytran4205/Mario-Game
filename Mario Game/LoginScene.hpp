#pragma once

#include "Scene.hpp"
#include "TextView.hpp"
// Include Manager
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"

constexpr float LOGINSCENE_SPACE_DISTANCE = 25;

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

	TextView m_title;
	// SpriteRenderer m_background;

public:
	LoginScene();
	~LoginScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

