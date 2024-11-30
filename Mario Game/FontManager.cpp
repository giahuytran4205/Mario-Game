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
	if (!m_font[FontType::ARIAL].loadFromFile("Resources/Fonts/ARIALBD 1.TTF")) {
		throw std::runtime_error("Failed to load ARIAL font.");
	}
	if (!m_font[FontType::SUPERMARIO256].loadFromFile("Resources/Fonts/SuperMario256.ttf")) {
		throw std::runtime_error("Failed to load SuperMario256 font.");
	}
}
