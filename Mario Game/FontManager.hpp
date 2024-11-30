#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SFML/Graphics.hpp"

enum FontType {
    ARIAL,
    SUPERMARIO256,
    NUM_FONTS
};

class FontManager
{
private:
    static FontManager* m_instance;
    sf::Font m_font[FontType::NUM_FONTS];
    void loadFonts();
public:
    static FontManager* getInstance();
    FontManager();
    ~FontManager();
    sf::Font& getFont(FontType fontType);
};
