#pragma once

#include "Object.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "TextView.hpp"
#include "SpriteRenderer.hpp"

class Panel : public Object
{
private:
	sf::Vector2f getContinueButtonSize();
	sf::Vector2f getExitButtonSize();
	sf::Vector2f getTitleSize();
	sf::Vector2f getTotalVolumeTextSize();
	sf::Vector2f getTotalVolumeSize();
	sf::Vector2f getThemeVolumeTextSize();
	sf::Vector2f getThemeVolumeSize();

	sf::Vector2f getContinueButtonPosition();
	sf::Vector2f getExitButtonPosition();
	sf::Vector2f getTitlePosition();
	sf::Vector2f getTotalVolumeTextPosition();
	sf::Vector2f getTotalVolumePosition();
	sf::Vector2f getThemeVolumeTextPosition();
	sf::Vector2f getThemeVolumePosition();

	Button m_continue;
	Button m_exit;
	TextView m_title;
	SpriteRenderer m_backgroundRenderer;
	RectangleShape m_background;

public:
	Panel(Object* parent = nullptr);
	~Panel();

	void render() override;
};
