#pragma once

#include "GUI.hpp"
#include "TextView.hpp"
#include <SFML/Graphics.hpp>

// Must have a sf::RenderWindow to draw the text in render() override funciton
// If calling Singleton in the GameManager, it will be a circle dependency: 
// 1. Button include GameManager
// 2. GameManager include LoginScene
// 3. Login Scene include Button
// There are the same problems in TextView Class, so we need to pass the sf::RenderWindow* to the Button and TextView
class Button : public GUI
{
private:	
	sf::RectangleShape m_rectShape;
	TextView m_textView;
	std::function<void()> m_action;
	
	// Mandatory
	sf::RenderWindow* m_window;

public:
	Button(Object* parent = nullptr);
	Button(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, const sf::Color& color, std::function<void()> action = nullptr, Object* parent = nullptr);
	~Button();

	void configure(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, const sf::Color& color, std::function<void()> action = nullptr);

	void setRenderWindow(sf::RenderWindow* window);
	//void setAction(std::function<void()> action);
	//void setPosition(const sf::Vector2f& position);
	//void setSize(const sf::Vector2f& size);
	//void setContent(const std::string& content);
	//void setFont(const sf::Font& font);
	//void setButtonFillColor(const sf::Color& color);
	//void setTextViewFillColor(const sf::Color& color);

	//void onHovered() override;
	//void onUnhovered() override;
	//void onPressed() override;
	//void onClick() override;
	void render() override;
};