#include "Panel.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "MapSelectionScene.hpp"

const float WIDTH_RATIO = 5.0f;
const float HEIGHT_RATIO = 5.0f;

sf::Vector2f Panel::getContinueButtonSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO, m_background.getSize().y / HEIGHT_RATIO * 0.5f);
}

sf::Vector2f Panel::getExitButtonSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO, m_background.getSize().y / HEIGHT_RATIO * 0.5f);
}

sf::Vector2f Panel::getTitleSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO * 3.0f, m_background.getSize().y / HEIGHT_RATIO);
}

sf::Vector2f Panel::getTotalVolumeTextSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO, m_background.getSize().y / HEIGHT_RATIO);
}

sf::Vector2f Panel::getTotalVolumeSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO * 2.0f, m_background.getSize().y / 2.0f);
}

sf::Vector2f Panel::getThemeVolumeTextSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO, m_background.getSize().y / HEIGHT_RATIO);
}

sf::Vector2f Panel::getThemeVolumeSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO * 2.0f, m_background.getSize().y / 2.0f);
}

sf::Vector2f Panel::getContinueButtonPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 1.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 4.0f);
}

sf::Vector2f Panel::getExitButtonPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 3.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 4.0f);
}

sf::Vector2f Panel::getTitlePosition()
{
    float titleWidth = getTitleSize().x;
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / 2.0f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO);
}

sf::Vector2f Panel::getTotalVolumeTextPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 2.0f);
}

sf::Vector2f Panel::getTotalVolumePosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 3.0f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 2.0f);
}

sf::Vector2f Panel::getThemeVolumeTextPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 3.0f);
}

sf::Vector2f Panel::getThemeVolumePosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 3.0f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 3.0f);
}

Panel::Panel(Object* parent) : 
    Object(parent),
	m_totalVolume(0, 100, getTotalVolumeSize().x, 0, getTotalVolumePosition(), this),
	m_themeVolume(0, 100, getThemeVolumeSize().x, 0, getThemeVolumePosition(), this)
{
    this->setEnable(false);

    const View& view = GameManager::getInstance()->getRenderWindow().getView();

    m_background.setFillColor(sf::Color::White);
    m_background.setSize(sf::Vector2f(view.getSize().x / 5.0f * 3.0f, view.getSize().y / 5.0f * 4.0f));
	m_background.setPosition(sf::Vector2f(view.getCenter().x - m_background.getSize().x / 2.0f, view.getCenter().y - m_background.getSize().y / 2.0f));

    m_continue.setParent(this);
    m_exit.setParent(this);

    m_continue.configure(getContinueButtonPosition(), getContinueButtonSize(), "Continue", FontManager::getInstance()->getFont("ARIAL"));
    m_exit.configure(getExitButtonPosition(), getExitButtonSize(), "Exit", FontManager::getInstance()->getFont("ARIAL"));

    m_continue.getComponent<Transform2D>().setRect(getContinueButtonPosition().x, getContinueButtonPosition().y, getContinueButtonSize().x, getContinueButtonSize().y);
    m_exit.getComponent<Transform2D>().setRect(getExitButtonPosition().x, getExitButtonPosition().y, getExitButtonSize().x, getExitButtonSize().y);

    m_continue.getText().setCharacterSize(12);
    m_exit.getText().setCharacterSize(12);

    m_continue.setAction([&]() {
        std::cout << "PANEL::Continue Button is Pressed" << std::endl;
        this->setEnable(false);
        });

    m_exit.setAction([&]() {
		std::cout << "PANEL::Exit Button is Pressed" << std::endl;
        });

    m_title.setParent(this);
    m_title.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_title.setCharacterSize(12);
	m_title.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_title.getComponent<Transform2D>().setSize(getTitleSize());
    m_title.getComponent<Transform2D>().setPosition(getTitlePosition());
    m_title.setString("Settings");

    m_totalVolume.setRenderOrder(20);
	m_themeVolume.setRenderOrder(20);
}

Panel::~Panel()
{
}

void Panel::render()
{
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}


