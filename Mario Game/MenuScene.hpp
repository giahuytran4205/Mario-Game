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
#include "SFML/Graphics.hpp"

#include <iostream>

std::string toUpperCase(const std::string& input) {
	std::string result = input;
	std::transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

class InputField;
class Button;
class TextView;
class Account;

class MenuScene : public Scene
{
private:
	sf::Vector2f m_getPlayerNameLabelSize(sf::RenderWindow& window);
	sf::Vector2f m_getPlayerNameTextSize(sf::RenderWindow& window);
	sf::Vector2f m_getMaxScoreLabelSize(sf::RenderWindow& window);
	sf::Vector2f m_getMaxScoreTextSize(sf::RenderWindow& window);
	sf::Vector2f m_getBackButtonSize(sf::RenderWindow& window);
	sf::Vector2f m_getNextButtonSize(sf::RenderWindow& window);

	sf::Vector2f m_getPlayerNameLabelPosition(sf::RenderWindow& window);
	sf::Vector2f m_getPlayerNameTextPosition(sf::RenderWindow& window);
	sf::Vector2f m_getMaxScoreLabelPosition(sf::RenderWindow& window);
	sf::Vector2f m_getMaxScoreTextPosition(sf::RenderWindow& window);
	sf::Vector2f m_getBackButtonPosition(sf::RenderWindow& window);
	sf::Vector2f m_getNextButtonPosition(sf::RenderWindow& window);

	void fitBackground(sf::Sprite* sprite, sf::RenderWindow& window);

	Account* m_account;
	TextView* m_playerNameLabel;
	TextView* m_playerNameText;
	TextView* m_maxScoreLabel;
	TextView* m_maxScoreText;
	Button* m_backButton;
	Button* m_nextButton;
	SpriteRenderer m_backgroundSprite;

public:
	MenuScene(Account* account);
	~MenuScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};