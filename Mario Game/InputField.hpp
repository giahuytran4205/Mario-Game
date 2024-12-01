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
	static InputField* currentlySelectedField;

	InputField(Object* parent, sf::RenderWindow& window, const float& x, const float& y, const float& width, const float& height, sf::Font& font);

	void onClick() override;
	void onKeyPressed(const sf::Event::TextEvent& textEvent) override;

	void setPosition(float x, float y);
	void setSize(float width, float height);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	std::string getContent();
	void clearContent();
	void render() override;
};