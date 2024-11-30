#pragma once

#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "GUI.hpp"
#include "GameManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

class InputField : public GUI
{
private:
	void adjustTextPosCharSizeInBox(sf::Text& text, const sf::RectangleShape& box);
	FRect getRectOfShape();

	sf::RectangleShape m_box;
	sf::Text m_text;
	std::string m_content;

	sf::RectangleShape m_cursor;
	bool m_cursorVisible = true;
	sf::Clock m_cursorBlinkClock;

public:
	//static InputField* currentlySelectedField;

	InputField(sf::RenderWindow& window, const float& x, const float& y, const float& width, const float& height, sf::Font& font);

	//void onSelected(const Event& event);
	//void onDeselect(const Event& event);
	//void onPressed(const Event& event);
	//void onHovered(const Event& event);
	//void onUnhovered(const Event& event);
	//void onClick(const Event& event);
	//void onDrag(const Vector2f& mousePos, const Event& event);
	//void handleEvent(const sf::Event& event) override;

	void onPressed() override;
	void onClick() override;
	void onKeyPressed(const sf::Event& event) override;

	void setPosition(float x, float y);
	void setSize(float width, float height);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	std::string getContent();
	void clearContent();

	void draw(sf::RenderWindow& target);
};