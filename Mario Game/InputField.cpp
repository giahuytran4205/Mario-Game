#include "InputField.hpp"

InputField* InputField::currentlySelectedField = nullptr;

void InputField::adjustTextPosCharSizeInBox()
{
    m_text.setString("Temp Text");

    float boxHeight = m_box.getSize().y;
    float boxWidth = m_box.getSize().x;

    m_text.setCharacterSize(20);

    while (true)
    {
        sf::FloatRect textBounds = m_text.getGlobalBounds();
        if (textBounds.height > boxHeight || textBounds.width > boxWidth)
        {
            m_text.setCharacterSize(m_text.getCharacterSize() - 1);
        }
        else
        {
            break;
        }
    }

    sf::FloatRect textBounds = m_text.getGlobalBounds();
    float textX = m_box.getPosition().x + boxWidth / 20.0f;
    float textY = m_box.getPosition().y + (boxHeight - textBounds.height) / 3.0f;
    m_text.setPosition(textX, textY);
    m_text.setString("");

    m_transform.getRect() = { m_box.getPosition().x, m_box.getPosition().y, m_box.getSize().x,  m_box.getSize().y };
}

InputField::InputField(Object* parent)
    : m_window(nullptr)
{
    setParent(parent);

    this->configure(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Font());
}

InputField::InputField(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, Object* parent)
    : m_window(nullptr)
{
    setParent(parent);

    this->configure(position, size, font);
}

void InputField::configure(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
{
    m_box.setPosition(position);
    m_box.setSize(size);
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineThickness(1.0f);
    m_box.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    this->adjustTextPosCharSizeInBox();
    m_text.setFillColor(sf::Color::Black);

    m_cursor.setSize(sf::Vector2f(2.f, m_text.getCharacterSize()));
    m_cursor.setFillColor(sf::Color::Black);
    m_cursorVisible = true;
    m_cursorBlinkClock.restart();
}

void InputField::setRenderWindow(sf::RenderWindow* window)
{
    if (window != nullptr)
    {
        m_window = window;
    }
}

void InputField::setPosition(const sf::Vector2f& position)
{
    m_box.setPosition(position);
    this->adjustTextPosCharSizeInBox();
    m_transform.getRect() = { position.x, position.y, m_box.getSize().x, m_box.getSize().y };
}

void InputField::setSize(const sf::Vector2f& size)
{
    m_box.setSize(size);
    this->adjustTextPosCharSizeInBox();
    m_transform.getRect() = { m_box.getPosition().x, m_box.getPosition().y, size.x, size.y };
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

void InputField::render()
{
    if (m_window != nullptr)
    {
        m_window->draw(m_box);
        m_text.setString(m_content);
        m_window->draw(m_text);
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
                m_window->draw(m_cursor);
            }
        }
    }
}
