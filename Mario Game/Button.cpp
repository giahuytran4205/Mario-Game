#include "Button.hpp"

Button::Button(Object* parent) 
	: m_window(nullptr)
{
	this->setParent(parent);

	configure(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "", sf::Font(), nullptr);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action, Object* parent) 
	: m_window(nullptr)
{
	this->setParent(parent);

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

void Button::setRenderWindow(sf::RenderWindow* window)
{
	if (window != nullptr)
	{
		m_window = window;
		m_textView.setRenderWindow(window);
	}
}

void Button::setAction(std::function<void()> action)
{
	if (action == nullptr)
	{
		std::cout << "Button::setAction: action is nullptr!" << std::endl;
		return;
	}

	m_action = action;
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
	if (m_window != nullptr)
	{
		m_window->draw(m_rectShape);
		// m_window->draw(m_textView);
	}
}
