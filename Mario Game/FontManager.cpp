#include "FontManager.hpp"

FontManager* FontManager::m_instance = nullptr;

void FontManager::loadFonts()
{
	m_font[FontType::ARIAL].loadFromFile("Resources\\TitleScene\\ARIALBD 1.TTF");
	m_font[FontType::SUPERMARIO256].loadFromFile("Resources\\TitleScene\\SuperMario256.ttf");
}

FontManager* FontManager::getInstance()
{
	return m_instance;
}

FontManager::FontManager()
{
	if (!m_instance)
	{
		m_instance = this;
	}
	loadFonts();
}

FontManager::~FontManager()
{
}

sf::Font& FontManager::getFont(FontType fontType)
{
	return m_font[fontType];
}
