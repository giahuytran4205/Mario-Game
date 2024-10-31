#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SpriteRenderer.hpp"
#include "Transform2D.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <sstream>
#include <map>

constexpr float MIN_FONT_SIZE = 8.0f;

class TextView
{
private:
    sf::Text m_text;
    sf::Font m_font;
    SpriteRenderer* m_spriteRender;

    void wrapAndFitText();

public:
	static std::map<std::string, sf::Font> allFonts; // fontName - Font, not fontPath - Font
    static void loadFontFromFile(const std::string fontName, const std::string& fontPath);

    TextView(SpriteRenderer* spriteRender, sf::Text text, const std::string& fontName, const std::string& fontPath);
	TextView(SpriteRenderer* spriteRender, sf::Text text, const sf::Font& font);

    void setText(const sf::Text& text);
    void setFont(const std::string& fontName, const std::string& fontPath);
	void setFont(const sf::Font& font);
    void setSpriteRender(SpriteRenderer* spriteRender);
	void setFillColor(const sf::Color& color);
};
