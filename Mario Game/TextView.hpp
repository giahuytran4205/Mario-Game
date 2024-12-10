#pragma once
#include "Rect.hpp"
#include "Object.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <map>

// Must have a sf::RenderWindow to draw the text in render() override funciton
// If calling Singleton in the GameManager, it will be a circle dependency: 
// 1. TextView include GameManager
// 2. GameManager include LoginScene
// 3. Login Scene include TextView
class TextView : public Object, public sf::Text {
private:
	void wrapText();

	FRect m_table;
	sf::RenderWindow* m_window;

public:
	TextView(Object* parent = nullptr);
	TextView(const FRect& table, const std::string& content, const sf::Font& font, Object* parent = nullptr);
	~TextView();

	void setRenderWindow(sf::RenderWindow* window);
	void configure(const FRect& table, const std::string& content, const sf::Font& font);

	void setTable(const FRect& table);
	const FRect& getTable() const;
	void render() override;
};