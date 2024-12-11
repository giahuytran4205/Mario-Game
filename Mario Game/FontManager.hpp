#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class FontManager
{
private:
    std::map<std::string, sf::Font> m_fonts;
    static std::unique_ptr<FontManager> m_instance;

    bool loadFont(const std::string& fontName, const std::string& filepath);

public:
    FontManager();
    ~FontManager() = default;

    static FontManager* getInstance();
    const sf::Font& getFont(const std::string& fontName);
};