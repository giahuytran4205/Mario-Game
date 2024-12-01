#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

class FontManager
{
public:
    static FontManager* m_instance;
    
    sf::Font m_font[FontType::NUM_FONTS];

    FontManager();
    ~FontManager();

    void loadFonts();
};