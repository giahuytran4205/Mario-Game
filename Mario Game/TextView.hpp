#pragma once
#include "Rect.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Must have a sf::RenderWindow to draw the text in render() override funciton
// If calling Singleton in the GameManager, it will be a circle dependency: 
// 1. TextView include GameManager
// 2. GameManager include LoginScene
// 3. Login Scene include TextView

constexpr float DEFAULT_RATIO_CHAR_SIZE_TABLE_HEIGHT = 0.33333f;

class TextView : public Object, public sf::Text {
private:
	void wrapText();

	FRect m_table;
	float m_ratioCharSizeTableHeight;
	// Mandatory
	sf::RenderWindow* m_window;

public:
	TextView(sf::RenderWindow* window = nullptr, Object* parent = nullptr);
	TextView(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font, sf::RenderWindow* window = nullptr, Object* parent = nullptr);
	~TextView();

	void setRenderWindow(sf::RenderWindow* window);
	void configure(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font);

	// Default ratio is 0.5f
	void setRatioCharacterSizeTableHeight(float ratio);
	void setTable(const FRect& table);
	void setTablePosition(const sf::Vector2f& tablePosition);
	void setTableSize(const sf::Vector2f& tableSize);
	const FRect& getTable() const;
	void render() override;
};