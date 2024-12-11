#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include "TextView.hpp"
#include "InputField.hpp"

constexpr float DIFFICULTSCENE_SPACE_DISTANCE = 25.0f;

class DifficultyScene : public Scene
{
private:
	sf::Vector2f getEasyButtonSize(sf::RenderWindow& window);
	sf::Vector2f getMediumButtonSize(sf::RenderWindow& window);
	sf::Vector2f getDifficultButtonSize(sf::RenderWindow& window);

	sf::Vector2f getEasyButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getMediumButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getDifficultButtonPosition(sf::RenderWindow& window);

	Button m_easy;
	Button m_medium;
	Button m_difficult;
	SpriteRenderer m_background;

public:
	DifficultyScene();
	~DifficultyScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

