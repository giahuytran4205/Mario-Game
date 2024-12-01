#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SpriteRenderer.hpp"
#include "Transform2D.hpp"
#include "SFML/Graphics.hpp"
#include "Rect.hpp"

#include <iostream>
#include <sstream>
#include <map>

constexpr unsigned int TEXT_SIZE_MIN = 15.0f;

class TextView {
private:
    void m_wrapText();

    sf::Text m_text;
    FRect m_table;
    std::string m_content;
public:
    TextView(const FRect& table, const std::string& textContent, sf::Font& textFont, const sf::Color& textColor, unsigned int textSize);

    TextView();
    void init(const FRect& table, const std::string& textContent, sf::Font& textFont, const sf::Color& textColor, unsigned int textSize);

    sf::Text& getText();

    void setTable(const FRect& table);
    void setContent(const std::string& s);
    void setFont(const sf::Font& font);
    void setFillColor(const sf::Color& color);
    void setScale(const sf::Vector2f& scale);
};