#include "Button.hpp"

Button::Button(Object* parent)
{
	this->setParent(parent);

	this->setRenderOrder(BUTTON_RECTSHAPE_DEFAULT_RENDER_ORDER);

	m_textView.setRenderOrder(BUTTON_TEXTVIEW_DEFAULT_RENDER_ORDER);
	m_textView.setParent(this);

	configure(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "", sf::Font(), nullptr);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, const std::string& content, const sf::Font& font, std::function<void()> action, Object* parent)
{
	this->setParent(parent);

	this->setRenderOrder(BUTTON_RECTSHAPE_DEFAULT_RENDER_ORDER);

	m_textView.setRenderOrder(BUTTON_TEXTVIEW_DEFAULT_RENDER_ORDER);
	m_textView.setParent(this);

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

	m_transform.setRect(position.x, position.y, size.x, size.y);
	m_transform.setAnchor(0.5, 0.5);

	m_textView.setFont(font);
	m_textView.setString(content);
	m_textView.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_textView.getComponent<Transform2D>().setPosition(0, 0);

	m_background.setAnchor(0.5, 0.5);
	m_background.setPosition(0, 0);
	m_background.setRenderOrder(2);

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
	m_textColor = color;
}

void Button::setTextViewRenderOrder(int renderOrder)
{
	m_textView.setRenderOrder(renderOrder);
}

void Button::setTexture(const Texture& texture) {
	m_background.setTexture(texture);
}

sf::Text& Button::getText() {
	return m_textView;
}

TextView& Button::getTextView() {
	return m_textView;
}

SpriteRenderer& Button::getBackground() {
	return m_background;
}

void Button::onHovered()
{
	m_textView.setFillColor(darkenColor(m_textColor, 30));
}

void Button::onUnhovered()
{
	m_textView.setFillColor(m_textColor);
}

void Button::onPressed()
{
	m_textView.setFillColor(darkenColor(m_textColor, 30));
	m_textView.setScale(sf::Vector2f(0.8f, 0.8f));

	m_background.scale(0.8f, 0.8f);
}

void Button::onDePressed() {
	m_textView.setScale(sf::Vector2f(1.0f, 1.0f));
	m_textView.setFillColor(m_textColor);

	m_background.scale(1.25f, 1.25f);
}

void Button::onClick()
{
	m_textView.setFillColor(darkenColor(m_textColor, 30));

	if (m_action != nullptr)
	{
		m_action();
	}
}

void Button::update() {
	m_textView.getComponent<Transform2D>().setSize(m_transform.getSize());
	m_rectShape.setSize(m_transform.getSize());
	m_rectShape.setOrigin(m_rectShape.getGlobalBounds().width * 0.5, m_rectShape.getGlobalBounds().height * 0.5);
	m_rectShape.setPosition(m_transform.getWorldCenter());
}

void Button::render()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	window.draw(m_rectShape);
	//window.draw(m_textView);
}
