#pragma once

#include "GUI.hpp"
#include "TextView.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>

constexpr int BUTTON_RECTSHAPE_DEFAULT_RENDER_ORDER = 0;
constexpr int BUTTON_TEXTVIEW_DEFAULT_RENDER_ORDER = 1;

class Button : public GUI
{
private:
	sf::RectangleShape m_rectShape;
	TextView m_textView;
	std::function<void()> m_action;

public:
	Button(Object* parent = nullptr);
	Button(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action = nullptr, Object* parent = nullptr);
	~Button();

	void configure(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action = nullptr);

	void setAction(std::function<void()> action);
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setContent(const std::string& content);
	void setFont(const sf::Font& font);
	void setButtonFillColor(const sf::Color& color);
	void setTextViewFillColor(const sf::Color& color);
	void setTextViewRenderOrder(int renderOrder);

	void onHovered() override;
	void onUnhovered() override;
	void onPressed() override;
	void onClick() override;
	void render() override;
};