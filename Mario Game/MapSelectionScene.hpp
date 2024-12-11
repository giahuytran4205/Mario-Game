#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include "TextView.hpp"
#include "InputField.hpp"

constexpr float MAPSELECTIONSCENE_SPACE_DISTANCE = 25.0f;

class MapSelectionScene : public Scene
{
private:
	sf::Vector2f getMap1ButtonSize(sf::RenderWindow& window);
	sf::Vector2f getMap2ButtonSize(sf::RenderWindow& window);
	sf::Vector2f getMap3ButtonSize(sf::RenderWindow& window);
	sf::Vector2f getMap4ButtonSize(sf::RenderWindow& window);
	sf::Vector2f getMap5ButtonSize(sf::RenderWindow& window);

	sf::Vector2f getMap1ButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getMap2ButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getMap3ButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getMap4ButtonPosition(sf::RenderWindow& window);
	sf::Vector2f getMap5ButtonPosition(sf::RenderWindow& window);

	Button m_map1;
	Button m_map2;
	Button m_map3;
	Button m_map4;
	Button m_map5;
	SpriteRenderer m_background;

public:
	MapSelectionScene();
	~MapSelectionScene();

	void update();
	void render();
	void handleEvent(const sf::Event& event);
};

