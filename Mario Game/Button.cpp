#include "Button.hpp"

//Button* m_selectedButton = nullptr;

FRect Button::getButtonRect()
{
	return { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

Button::Button(Object* parent, sf::RenderWindow& window, float x, float y, float width, float height, const std::string& labelContent, sf::Font& labelFont, sf::Color labelColor, std::function<void()> action)
{
	setParent(parent);
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(0);
	m_shape.setOutlineColor(sf::Color::White);

	this->setPosition(x, y);

	unsigned int textSize = m_shape.getSize().y / 3;

	m_label.init(this, this->getButtonRect(), labelContent, labelFont, labelColor, textSize);

	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };

	m_action = action;
	m_parent = parent;
}

Button::~Button()
{
}

void Button::setLabel(const std::string& s)
{
	m_label.setContent(s);
}

void Button::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
	m_label.setTable(this->getButtonRect());
	m_transform.getRect() = { x, y, m_shape.getSize().x, m_shape.getSize().y };
}

void Button::setSize(float width, float height)
{
	m_shape.setSize({ width, height });
	m_label.setTable(this->getButtonRect());
	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

void Button::setContentScale(float x, float y)
{
	m_label.setScale({ x, y });
}

void Button::onHovered()
{
	m_label.setFillColor(sf::Color::White);
}

void Button::onUnhovered()
{
	m_label.setFillColor(sf::Color::Black);
}

void Button::onPressed()
{
	m_label.setFillColor(sf::Color::White);
	m_label.setScale({ 0.8f, 0.8f });
}

void Button::onClick()
{
	m_label.setScale({ 1.0f, 1.0f });
	m_label.setFillColor(sf::Color::White);

	if (m_action)
		m_action();
}

void Button::setAction(std::function<void()> action)
{
	m_action = action;
}

void Button::draw(sf::RenderWindow& target)
{
	target.draw(m_shape);
	target.draw(m_label.getText());
}