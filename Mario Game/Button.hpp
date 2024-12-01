#pragma once

#include "Common.hpp"
#include "GUI.hpp"
#include "TextView.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "GameManager.hpp"
#include "Rect.hpp"

constexpr unsigned int DEFAULT_TEXT_SIZE = 50;

class TextView;

class Button : public GUI
{
private:
	FRect getButtonRect();

	sf::RectangleShape m_shape;
	TextView* m_label;
	std::function<void()> m_action;

public:
	Button(Object* parent, sf::RenderWindow& window, float x, float y, float width, float height, const std::string& labelContent, sf::Font& labelFont, sf::Color labelColor, std::function<void()> action = nullptr);
	~Button();

	void setLabel(const std::string& s);
	void setPosition(float x, float y);
	void setSize(float width, float height);
	void setContentScale(float x, float y);

	void onHovered() override;
	void onUnhovered() override;
	void onPressed() override;
	void onClick() override;
	void setAction(std::function<void()> action);
	void render() override;
};