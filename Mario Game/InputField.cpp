#include "InputField.hpp"

InputField* InputField::currentlySelectedField = nullptr;

FRect InputField::getRectOfShape()
{
    return { m_box.getPosition().x, m_box.getPosition().y, m_box.getSize().x,  m_box.getSize().y };
}

void InputField::adjustTextPosCharSizeInBox(sf::Text& text, const sf::RectangleShape& box)
{
    text.setString("Temp Text");

    float boxHeight = box.getSize().y;
    float boxWidth = box.getSize().x;

    text.setCharacterSize(20);

    while (true)
    {
        sf::FloatRect textBounds = text.getGlobalBounds();
        if (textBounds.height > boxHeight || textBounds.width > boxWidth)
        {
            text.setCharacterSize(text.getCharacterSize() - 1);
        }
        else
        {
            break;
        }
    }

    sf::FloatRect textBounds = text.getGlobalBounds();
    float textX = box.getPosition().x + boxWidth / 20.0f;
    float textY = box.getPosition().y + (boxHeight - textBounds.height) / 3.0f;
    text.setPosition(textX, textY);
    text.setString("");

    m_transform.getRect() = { m_box.getPosition().x, m_box.getPosition().y, m_box.getSize().x,  m_box.getSize().y };
}

InputField::InputField(sf::RenderWindow& window, const float& x, const float& y, const float& width, const float& height, sf::Font& font)
{
    m_window = &window;
    m_box.setSize({ width, height });
    m_box.setPosition({ x, y });
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineThickness(1.5);
    m_box.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    adjustTextPosCharSizeInBox(m_text, m_box);
    m_text.setFillColor(sf::Color::Black);

    m_cursor.setSize({ 2.f, 24.f });
    m_cursor.setFillColor(sf::Color::Black);
    m_cursorVisible = true;
    m_cursorBlinkClock.restart();
}

void InputField::onClick()
{
    currentlySelectedField = this;
}

void InputField::onKeyPressed(const sf::Event::TextEvent& textEvent)
{
    if (currentlySelectedField == this)
    {
        if (textEvent.unicode == 8)
        {
            if (!m_content.empty())
            {
                m_content.pop_back();
                m_text.setString(m_content);
            }
        }
        else if (textEvent.unicode >= 32 && textEvent.unicode < 127)
        {
            m_content += static_cast<char>(textEvent.unicode);
            m_text.setString(m_content);
        }
    }
}

void InputField::setPosition(float x, float y)
{
    m_box.setPosition(x, y);
    this->adjustTextPosCharSizeInBox(m_text, m_box);
    FRect newRect = { x, y, m_box.getSize().x, m_box.getSize().y };
    m_transform.getRect() = newRect;
}

void InputField::setSize(float width, float height)
{
    m_box.setSize({ width, height });
    this->adjustTextPosCharSizeInBox(m_text, m_box);
    FRect newRect = { m_box.getPosition().x, m_box.getPosition().y, m_box.getSize().x, m_box.getSize().y };
    m_transform.getRect() = newRect;
}

sf::Vector2f InputField::getPosition()
{
    return m_box.getPosition();
}

sf::Vector2f InputField::getSize()
{
    return m_box.getSize();
}

std::string InputField::getContent()
{
    return m_text.getString();
}

void InputField::clearContent()
{
    m_content.clear();
    m_text.setString(m_content);
}

void InputField::draw(sf::RenderWindow& target)
{
    target.draw(m_box);
    m_text.setString(m_content);
    target.draw(m_text);

    if (m_isSelected)
    {
        if (m_cursorBlinkClock.getElapsedTime().asSeconds() >= 0.5f)
        {
            m_cursorVisible = !m_cursorVisible;
            m_cursorBlinkClock.restart();
        }

        if (m_cursorVisible)
        {
            sf::FloatRect textBounds = m_text.getLocalBounds();

            float cursorX = m_text.getPosition().x + textBounds.width + 1.f;
            float cursorY = m_text.getPosition().y;
            m_cursor.setPosition(cursorX, cursorY);
            target.draw(m_cursor);
        }
    }
}