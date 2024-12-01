#include "TextView.hpp"

void TextView::m_wrapText()
{
    float maxWidth = m_table.width;
    float maxHeight = m_table.height;
    unsigned int textSize = m_text.getCharacterSize();

    unsigned int initialTextSize = textSize;

    while (true)
    {
        std::string wrappedText;
        std::string currentLine;
        std::istringstream wordStream(m_content);

        m_text.setCharacterSize(textSize);
        std::string word;

        while (wordStream >> word)
        {
            std::string tempLine = currentLine + word + " ";
            m_text.setString(tempLine);

            if (m_text.getLocalBounds().width > maxWidth)
            {
                wrappedText += currentLine + "\n";
                currentLine = word + " ";
            }
            else
            {
                currentLine = tempLine;
            }
        }
        wrappedText += currentLine;
        m_text.setString(wrappedText);

        if (m_text.getLocalBounds().height <= maxHeight && m_text.getLocalBounds().width <= maxWidth)
        {
            break;
        }

        textSize -= 1;
        if (textSize <= TEXT_SIZE_MIN)
        {
            break;
        }
    }

    m_text.setCharacterSize(textSize * 1.3f);

    sf::FloatRect textBounds = m_text.getLocalBounds();

    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    m_text.setPosition(m_table.left + m_table.width / 2.0f,
        m_table.top + m_table.height / 2.0f);
}

TextView::TextView()
{
    m_table = { 0, 0, 0, 0 };
    m_content = "";
    m_text.setString(m_content);
    m_text.setCharacterSize(0);
    m_text.setFillColor(sf::Color::White);
}

TextView::TextView(Object* parent, const FRect& table, const std::string& textContent, sf::Font& textFont, const sf::Color& textColor, unsigned int textSize)
{
    setParent(parent);
    m_table = table;
    m_content = textContent;
    m_text.setString(m_content);
    m_text.setFont(textFont);
    m_text.setCharacterSize(textSize);
    m_text.setFillColor(textColor);
    m_wrapText();
}

void TextView::init(Object* parent, const FRect& table, const std::string& textContent, sf::Font& textFont, const sf::Color& textColor, unsigned int textSize)
{
    setParent(parent);
    m_table = table;
    m_content = textContent;
    m_text.setString(m_content);
    m_text.setFont(textFont);
    m_text.setCharacterSize(textSize);
    m_text.setFillColor(textColor);
    m_wrapText();
}

sf::Text& TextView::getText()
{
    return m_text;
}

void TextView::setTable(const FRect& table)
{
    m_table = table; // Error at this line
    m_wrapText();
}

void TextView::setContent(const std::string& s)
{
    m_content = s;
    m_text.setString(m_content);
    m_wrapText();
}

void TextView::setFont(const sf::Font& font)
{
    m_text.setFont(font);
    m_wrapText();
}

void TextView::setFillColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void TextView::setScale(const sf::Vector2f& scale)
{
    m_text.setScale(scale);
}

void TextView::render()
{
    GameManager::getInstance()->getRenderWindow().draw(m_text);
}
