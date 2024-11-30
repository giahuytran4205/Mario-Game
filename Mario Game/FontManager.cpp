#include "FontManager.hpp"

FontManager* FontManager::m_instance = nullptr;

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

void FontManager::loadFonts()
{
	if (m_font[FontType::ARIAL].loadFromFile("Resources/Fonts/ARIALBD 1.TTF")) {
		std::cout << "Load Arial Font Successfully" << std::endl;
	}
	if (m_font[FontType::SUPERMARIO256].loadFromFile("Resources/Fonts/SuperMario256.ttf")) {
		std::cout << "Load SuperMario256 Font Successfully" << std::endl;
	}
}
