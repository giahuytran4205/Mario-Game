#include "Button.hpp"

//Button* m_selectedButton = nullptr;

FRect Button::getButtonRect()
{
	return { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

Button::Button(Object* parent)
{
	setParent(parent);
	m_action = nullptr;

	m_shape.setSize(sf::Vector2f(100, 100));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(0);
	m_shape.setOutlineColor(sf::Color::White);

	unsigned int textSize = m_shape.getSize().y / 3;

	m_label = new TextView(this, this->getButtonRect(), "", FontManager::m_instance->m_font[FontType::ARIAL], sf::Color::Black, 20);

	this->setPosition(0, 0);

	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

void Button::init(float x, float y, float width, float height, const std::string& labelContent, sf::Font& labelFont, sf::Color labelColor, std::function<void()> action)
{
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(0);
	m_shape.setOutlineColor(sf::Color::White);

	unsigned int textSize = m_shape.getSize().y / 3;

	m_label = new TextView(this, this->getButtonRect(), labelContent, labelFont, labelColor, textSize);

	this->setPosition(x, y);

	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };

	m_action = action;
}

Button::Button(Object* parent, sf::RenderWindow& window, float x, float y, float width, float height, const std::string& labelContent, sf::Font& labelFont, sf::Color labelColor, std::function<void()> action)
{
	setParent(parent);
	m_window = &window;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(0);
	m_shape.setOutlineColor(sf::Color::White);

	unsigned int textSize = m_shape.getSize().y / 3;

	m_label = new TextView(this, this->getButtonRect(), labelContent, labelFont, labelColor, textSize);

	this->setPosition(x, y);

	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };

	m_action = action;
}

Button::~Button()
{
	delete m_label;
}

void Button::setLabelContent(const std::string& s)
{
	m_label->setContent(s);
}

void Button::setPosition(float x, float y)
{
	m_shape.setPosition(x, y);
	m_label->setTable(this->getButtonRect());
	m_transform.getRect() = { x, y, m_shape.getSize().x, m_shape.getSize().y };
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
	m_label->setTable(this->getButtonRect());
	m_transform.getRect() = { position.x, position.y, m_shape.getSize().x, m_shape.getSize().y };
}

void Button::setSize(float width, float height)
{
	m_shape.setSize({ width, height });
	m_label->setTable(this->getButtonRect());
	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

void Button::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
	m_label->setTable(this->getButtonRect());
	m_transform.getRect() = { m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x,  m_shape.getSize().y };
}

void Button::setContentScale(float x, float y)
{
	m_label->setScale({ x, y });
}

void Button::setTextFont(sf::Font& font)
{
	m_label->setFont(font);
}

void Button::setTextColor(sf::Color color)
{
	m_label->setFillColor(color);
}

void Button::setAction(std::function<void()> action)
{
	m_action = action;
}

void Button::setScaleTextSize(float scale)
{
	m_label->setScaleTextSize(0.5f);
}

void Button::onHovered()
{
	m_label->setFillColor(sf::Color::White);
}

void Button::onUnhovered()
{
	m_label->setFillColor(sf::Color::Black);
}

void Button::onPressed()
{
	m_label->setFillColor(sf::Color::White);
	m_label->setScale({ 0.8f, 0.8f });
}

void Button::onClick()
{
	m_label->setScale({ 1.0f, 1.0f });
	m_label->setFillColor(sf::Color::White);

	if (m_action)
		m_action();
}

void Button::render()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	window.draw(m_shape);
	//m_label.render();
}