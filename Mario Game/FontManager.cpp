#include "FontManager.hpp"

std::unique_ptr<FontManager> FontManager::m_instance = nullptr;

bool FontManager::loadFont(const std::string& fontName, const std::string& filepath)
{
    if (m_fonts.find(fontName) != m_fonts.end())
    {
        std::cout << "Font '" << fontName << "' is already loaded." << std::endl;
        return true;
    }

    sf::Font font;
    if (font.loadFromFile(filepath))
    {
        m_fonts[fontName] = font;
        std::cout << "Font '" << fontName << "' loaded successfully." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed to load font '" << fontName << "'!" << std::endl;
        return false;
    }
}

FontManager::FontManager()
{
    if (!loadFont("ARIAL", "Resources/Fonts/ARIALBD 1.TTF"))
    {
        std::cout << "FontManager::Failed to load ARIAL font!" << std::endl;
    }

    if (!loadFont("SUPERMARIO256", "Resources/Fonts/SuperMario256.ttf"))
    {
        std::cout << "FontManager::Failed to load SuperMario256 font!" << std::endl;
    }
}

FontManager* FontManager::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = std::make_unique<FontManager>();
    }

    return m_instance.get();
}

const sf::Font& FontManager::getFont(const std::string& fontName)
{
    if (m_instance == nullptr)
    {
        std::cout << "FontManager is not initialized!" << std::endl;
        static sf::Font defaultFont;
        return defaultFont;
    }

    auto it = m_instance->m_fonts.find(fontName);
    if (it == m_instance->m_fonts.end())
    {
        std::cout << "Font '" << fontName << "' is not loaded!" << std::endl;
        static sf::Font defaultFont;
        return defaultFont;
    }

    return it->second;
}