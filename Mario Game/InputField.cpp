#include "InputField.hpp"

//InputField* InputField::currentlySelectedField = nullptr;

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

//void InputField::onSelected(const Event& event)
//{
//    if (event.type == Event::TextEntered)
//    {
//        if (event.text.unicode == 8)
//        {
//            if (!m_content.empty())
//            {
//                m_content.pop_back();
//                m_text.setString(m_content);
//            }
//        }
//        else if (event.text.unicode >= 32 && event.text.unicode < 127)
//        {
//            m_content += static_cast<char>(event.text.unicode);
//            m_text.setString(m_content);
//        }
//    }
//}
//
//void InputField::onDeselect(const Event& event) {}
//
//void InputField::onPressed(const Event& event)
//{
//    m_box.setFillColor(sf::Color::Red);
//}
//
//void InputField::onHovered(const Event& event) {}
//
//void InputField::onUnhovered(const Event& event) {}
//
//void InputField::onClick(const Event& event)
//{
//    m_box.setFillColor(sf::Color::White);
//}
//
//void InputField::onDrag(const Vector2f& mousePos, const Event& event) {}
//
//void InputField::handleEvent(const Event& event) {
//    Vector2f dist = m_window->getView().getCenter() - m_window->getDefaultView().getCenter();
//    if (isInteractable()) {
//        if (m_transform.getRect().contains((Vector2f)Mouse::getPosition(*m_window) + dist)) {
//            m_isHovered = true;
//            onHovered(event);
//
//            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
//                m_isPressed = true;
//                m_isOnDrag = true;
//                onPressed(event);
//            }
//
//            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
//                m_isPressed = false;
//                m_isOnDrag = false;
//
//                if (currentlySelectedField != this) {
//                    // Deselect the previously selected InputField
//                    if (currentlySelectedField != nullptr) {
//                        currentlySelectedField->m_isSelected = false;
//                    }
//                    // Set the current InputField as selected
//                    currentlySelectedField = this;
//                    m_isSelected = true;
//                }
//
//                onClick(event);
//            }
//        }
//        else
//        {
//            if (isHovered()) onUnhovered(event);
//            m_isHovered = false;
//        }
//
//        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
//            m_isOnDrag = false;
//
//        if (isOnDrag() && event.type == Event::MouseMoved) {
//            onDrag((Vector2f)Mouse::getPosition(*m_window) + dist, event);
//        }
//
//        if (isSelected())
//        {
//            onSelected(event);
//        }
//        else
//        {
//            onDeselect(event);
//        }
//    }
//}

void InputField::onKeyPressed(const sf::Event& event)
{
    if (event.type == Event::TextEntered)
    {
        if (event.text.unicode == 8)
        {
            if (!m_content.empty())
            {
                m_content.pop_back();
                m_text.setString(m_content);
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127)
        {
            m_content += static_cast<char>(event.text.unicode);
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

void InputField::draw(sf::RenderTarget& target)
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