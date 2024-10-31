#include "Button.hpp"

Button::Button(sf::RenderWindow& window, const sf::Texture& defaultTexture, const sf::Texture& hoveredTexture, const sf::Texture& pressedTexture, const sf::Text text, const sf::Font font, void(*action)(), Object* parent)
{
	m_window = &window;
	m_defaultTexture = defaultTexture;
	m_hoveredTexture = hoveredTexture;
	m_pressedTexture = pressedTexture;
	m_text = new TextView(&m_background, text, font);
	m_text->setFillColor(sf::Color::Cyan);
	m_action = action;
	m_parent = parent;
}

Button::Button(sf::RenderWindow& window, const sf::Texture& texture, const sf::Text text, const sf::Font font, void(*action)(), Object* parent) : Button(window, texture, texture, texture, text, font, action, parent) {}

Button::~Button() {}

void Button::setDefaultTexture(const Texture& defaultTexture)
{
	m_defaultTexture = defaultTexture;
}

void Button::setHoveredTexture(const Texture& hoveredTexture)
{
	m_hoveredTexture = hoveredTexture;
}

void Button::setPressedTexture(const Texture& pressedTexture)
{
	m_pressedTexture = pressedTexture;
}

void Button::setFont(const sf::Font& font)
{
	m_text->setFont(font);
}

void Button::setText(const sf::Text& text)
{
	m_text->setText(text);
}

void Button::onHovered()
{
	if (m_isHovered)
	{
		m_text->setFillColor(sf::Color::White);
		m_background.setTexture(m_hoveredTexture);
	}
}

void Button::onPressed()
{
	if (m_isPressed)
	{
		m_text->setFillColor(sf::Color::Black);
		m_background.setTexture(m_pressedTexture);
		m_background.getSprite().setScale(0.95f, 0.95f);
	}
}

void Button::onClick()
{
	if (m_isPressed)
	{
		m_text->setFillColor(sf::Color::Cyan);
		m_background.setTexture(m_defaultTexture);
		m_background.getSprite().setScale(1.0f, 1.0f);
		if (m_action)
			m_action();
	}
}

void Button::setAction(void(*func)())
{
	m_action = func;
}
