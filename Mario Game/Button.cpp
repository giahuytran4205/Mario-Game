#include "Button.hpp"

Button::Button(Object* parent)
{
	this->setParent(parent);

	this->setRenderOrder(BUTTON_RECTSHAPE_DEFAULT_RENDER_ORDER);

	m_textView.setRenderOrder(BUTTON_TEXTVIEW_DEFAULT_RENDER_ORDER);

	configure(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "", sf::Font(), nullptr);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action, Object* parent)
{
	this->setParent(parent);

	this->setRenderOrder(BUTTON_RECTSHAPE_DEFAULT_RENDER_ORDER);

	m_textView.setRenderOrder(BUTTON_TEXTVIEW_DEFAULT_RENDER_ORDER);

	configure(position, size, content, font, action);
}

Button::~Button()
{
}

void Button::configure(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action)
{
	m_rectShape.setPosition(position);
	m_rectShape.setSize(size);
	m_rectShape.setFillColor(sf::Color::Transparent);

	m_transform.getRect() = { position.x, position.y, size.x, size.y };

	m_textView.configure(position, size, content, font);

	m_action = action;
}

void Button::setAction(std::function<void()> action)
{
	if (action != nullptr)
	{
		m_action = action;
	}
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_rectShape.setPosition(position);
	m_textView.setTablePosition(position);
}

void Button::setSize(const sf::Vector2f& size)
{
	m_rectShape.setSize(size);
	m_textView.setTableSize(size);
}

void Button::setContent(const std::string& content)
{
	m_textView.setString(content);
}

void Button::setFont(const sf::Font& font)
{
	m_textView.setFont(font);
}

void Button::setButtonFillColor(const sf::Color& color)
{
	m_rectShape.setFillColor(color);
}

void Button::setTextViewFillColor(const sf::Color& color)
{
	m_textView.setFillColor(color);
}

void Button::setTextViewRenderOrder(int renderOrder)
{
	m_textView.setRenderOrder(renderOrder);
}

void Button::onHovered()
{
	m_textView.setFillColor(sf::Color::White);
}

void Button::onUnhovered()
{
	m_textView.setFillColor(sf::Color::Black);
}

void Button::onPressed()
{
	m_textView.setFillColor(sf::Color::White);
	m_textView.setScale(sf::Vector2f(0.8f, 0.8f));
}

void Button::onClick()
{
	m_textView.setFillColor(sf::Color::White);
	m_textView.setScale(sf::Vector2f(1.0f, 1.0f));

	if (m_action != nullptr)
	{
		m_action();
	}
}

void Button::render()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	window.draw(m_rectShape);
	//window.draw(m_textView);
}
