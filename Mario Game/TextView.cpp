#include "TextView.hpp"

std::map<std::string, sf::Font> TextView::allFonts;

void TextView::wrapAndFitText()
{
    gr::Rect rect = m_spriteRender->m_entity->getComponent<Transform2D>().getRect();
    float maxWidth = rect.width;
    float maxHeight = rect.height;
    std::string wrappedText;
    std::string currentLine;

    std::istringstream wordStream(m_text.getString().toAnsiString());
    std::string word;
    float fontSize = static_cast<float>(m_text.getCharacterSize());

    while (true)
    {
        wrappedText.clear();
        currentLine.clear();
        m_text.setCharacterSize(static_cast<unsigned int>(fontSize));
        wordStream.clear();
        wordStream.seekg(0);

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

        if (m_text.getLocalBounds().height <= maxHeight)
            break;

        fontSize -= 1.0f;
        if (fontSize <= MIN_FONT_SIZE)
            break;
    }
}

void TextView::loadFontFromFile(const std::string fontName, const std::string& fontPath)
{
    if (allFonts.find(fontName) == allFonts.end())
    {
        sf::Font font;

        if (font.loadFromFile(fontPath))
            allFonts[fontName] = font;
        else {
            //std::cout << "ERROR::TEXTVIEW::LOAD_FONT_FROM_FILE::Failed to load font from file: " << fontPath << std::endl;
        }
    }
}

TextView::TextView(SpriteRenderer* spriteRender, sf::Text text, const std::string& fontName, const std::string& fontPath)
{
    m_spriteRender = spriteRender;
    m_text = text;
    setFont(fontName, fontPath);
    wrapAndFitText();
}

TextView::TextView(SpriteRenderer* spriteRender, sf::Text text, const sf::Font& font)
{
	m_spriteRender = spriteRender;
	m_text = text;
	m_font = font;
	m_text.setFont(m_font);
	wrapAndFitText();
}

void TextView::setText(const sf::Text& text)
{
    m_text = text;
    wrapAndFitText();
}

void TextView::setFont(const std::string& fontName, const std::string& fontPath)
{
    if (allFonts.find(fontPath) == allFonts.end())
        loadFontFromFile(fontName, fontPath);
    
    m_font = allFonts[fontPath];
    m_text.setFont(m_font);
    wrapAndFitText();
}

void TextView::setFont(const sf::Font& font)
{
	m_font = font;
	m_text.setFont(m_font);
	wrapAndFitText();
}

void TextView::setSpriteRender(SpriteRenderer* spriteRender)
{
    m_spriteRender = spriteRender;
    wrapAndFitText();
}

void TextView::setFillColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}
