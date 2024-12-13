#pragma once

#include "Rect.hpp"
#include "GUI.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

constexpr int INPUTFIELD_DEFAULT_RENDER_ORDER = 0;

class InputField : public GUI
{
private:
	static InputField* currentlySelectedField;

	void adjustTextPosCharSizeInBox();

	sf::RectangleShape m_box;
	sf::Text m_text;
	std::string m_content;

	sf::RectangleShape m_cursor;
	bool m_cursorVisible = true;
	sf::Clock m_cursorBlinkClock;

public:
	InputField(Object* parent = nullptr);
	InputField(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, Object* parent = nullptr);

	void configure(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	std::string getContent();
	void clearContent();

	void onClick() override;
	void onKeyPressed(const sf::Event::TextEvent& textEvent) override;
	void render() override;
};