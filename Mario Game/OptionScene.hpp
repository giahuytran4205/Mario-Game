#pragma once

#include "GameManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "InputField.hpp"
#include "Slider.hpp"
#include "Enum.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "SFML/Graphics.hpp"

class TextView;
class Button;
class InputField;
template<typename T>
class Slider;

class OptionScene : public Scene
{
private:
	// GET SIZE OBJECT FUNCTIONS
	sf::Vector2f m_getThemeVolumeSize(sf::RenderWindow& window);
	sf::Vector2f m_getTotalVolumeSize(sf::RenderWindow& window);
	sf::Vector2f m_getEffectVolumeSize(sf::RenderWindow& window);
	sf::Vector2f m_getContinueButtonSize(sf::RenderWindow& window);
	sf::Vector2f m_getHomeButtonSize(sf::RenderWindow& window);
	sf::Vector2f m_getExitButtonSize(sf::RenderWindow& window);

	// GET POSITION OBJECT FUNTIONS
	sf::Vector2f m_getThemeVolumePostion(sf::RenderWindow& window);
	sf::Vector2f m_getTotalVolumePostion(sf::RenderWindow& window);
	sf::Vector2f m_getEffectVolumePostion(sf::RenderWindow& window);
	sf::Vector2f m_getContinueButtonPostion(sf::RenderWindow& window);
	sf::Vector2f m_getHomeButtonPostion(sf::RenderWindow& window);
	sf::Vector2f m_getExitButtonPostion(sf::RenderWindow& window);

	void fitBackground(sf::Sprite* sprite, sf::RenderWindow& window)
	{
		if (sprite->getTexture() != nullptr)
		{
			sf::Vector2u textureSize = sprite->getTexture()->getSize();
			sf::Vector2u windowSize = window.getSize();

			float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
			float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

			sprite->setScale(scaleX, scaleY);
		}
	}

	Slider<float> m_totalVolume;
	Slider<float> m_themeVolume;
	Slider<float> m_effectVolume;
	Button* m_continue;
	Button* m_home;
	Button* m_exit;
	SpriteRenderer m_background;

public:
	OptionScene();
	~OptionScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

