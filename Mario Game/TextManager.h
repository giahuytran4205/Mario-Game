#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"

#include <map>

class TextManager
{
private:
	sf::Text m_text;
	sf::Font m_font;
	SpriteRenderer* m_sprite;

public:
	static std::map< std::string, sf::Font> _fonts;
	void loadFont(const std::string& fontName, const std::string& fontPath);
	sf::Font& getFont(const std::string& fontName);
	void setText(const std::string& text);
	void setFont(const std::string& fontName);
	
};

