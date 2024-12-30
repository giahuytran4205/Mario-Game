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
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO * 3.0f, m_background.getSize().y / 2.0f);
}

sf::Vector2f Panel::getThemeVolumeTextSize()
{
    return sf::Vector2f(m_background.getSize().x / WIDTH_RATIO, m_background.getSize().y / HEIGHT_RATIO);
}

sf::Vector2f Panel::getThemeVolumeSize()
{
    return getTotalVolumeSize();
}

sf::Vector2f Panel::getContinueButtonPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 1.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 4.2f);
}

sf::Vector2f Panel::getExitButtonPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 3.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 4.2f);
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
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 0.9f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 2.2f);
}

sf::Vector2f Panel::getTotalVolumePosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 1.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 2.2f);
}

sf::Vector2f Panel::getThemeVolumeTextPosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 0.9f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 3.2f);
}

sf::Vector2f Panel::getThemeVolumePosition()
{
    return sf::Vector2f(
        m_background.getPosition().x + m_background.getSize().x / WIDTH_RATIO * 1.5f,
        m_background.getPosition().y + m_background.getSize().y / HEIGHT_RATIO * 3.2f);
}

Panel::Panel(Object* parent) : 
    Object(parent),
	m_totalVolume(0, 100, 140, 0, {0, 0}, this),
	m_themeVolume(0, 100, 140, 0, {0, 0}, this)
{
    this->setEnable(false);

    const View& view = GameManager::getInstance()->getRenderWindow().getView();

    m_background.setFillColor(sf::Color::Black);
    m_background.setSize(sf::Vector2f(view.getSize().x / 5.0f * 3.0f, view.getSize().y / 5.0f * 4.0f));
	m_background.setPosition(sf::Vector2f(view.getCenter().x - m_background.getSize().x / 2.0f, view.getCenter().y - m_background.getSize().y / 2.0f));

    m_background2.setFillColor(sf::Color::Cyan);
	m_background2.setSize(sf::Vector2f(m_background.getSize().x - 10.0f * 2, m_background.getSize().y - 10.0f * 2));
    m_background2.setPosition(sf::Vector2f(m_background.getPosition().x + 10.0f, m_background.getPosition().y + 10.0f));

	m_totalVolume.setPostion(getTotalVolumePosition());
	m_themeVolume.setPostion(getThemeVolumePosition());

    m_continue.setParent(this);
    m_exit.setParent(this);

    m_continue.configure(getContinueButtonPosition(), getContinueButtonSize(), "Continue", FontManager::getInstance()->getFont("ARIAL"));
    m_exit.configure(getExitButtonPosition(), getExitButtonSize(), "Exit", FontManager::getInstance()->getFont("ARIAL"));

    m_continue.getComponent<Transform2D>().setRect(getContinueButtonPosition().x, getContinueButtonPosition().y, getContinueButtonSize().x, getContinueButtonSize().y);
    m_exit.getComponent<Transform2D>().setRect(getExitButtonPosition().x, getExitButtonPosition().y, getExitButtonSize().x, getExitButtonSize().y);

    m_continue.getText().setCharacterSize(10);
    m_exit.getText().setCharacterSize(10);

    m_continue.setAction([&]() {
        std::cout << "PANEL::Continue Button is Pressed" << std::endl;
        this->setEnable(false);
        });

    m_exit.setAction([&]() {
		std::cout << "PANEL::Exit Button is Pressed" << std::endl;
        });

    m_continue.setButtonFillColor(sf::Color::Yellow);
    m_continue.setTextViewFillColor(sf::Color::Red);
	m_exit.setButtonFillColor(sf::Color::Yellow);
	m_exit.setTextViewFillColor(sf::Color::Red);

    m_title.setParent(this);
    m_title.setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));
	m_title.setCharacterSize(18);
	m_title.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_title.getComponent<Transform2D>().setSize(getTitleSize());
    m_title.getComponent<Transform2D>().setPosition(getTitlePosition());
    m_title.setString("Settings");

    m_totalVolumeText.setParent(this);
	m_totalVolumeText.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_totalVolumeText.setCharacterSize(9);
	m_totalVolumeText.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
	m_totalVolumeText.getComponent<Transform2D>().setSize(getTotalVolumeTextSize());
	m_totalVolumeText.getComponent<Transform2D>().setPosition(getTotalVolumeTextPosition());
    m_totalVolumeText.setString("Total Vol");

    m_themeVolumeText.setParent(this);
    m_themeVolumeText.setFont(FontManager::getInstance()->getFont("ARIAL"));
    m_themeVolumeText.setCharacterSize(9);
    m_themeVolumeText.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
    m_themeVolumeText.getComponent<Transform2D>().setSize(getThemeVolumeTextSize());
    m_themeVolumeText.getComponent<Transform2D>().setPosition(getThemeVolumeTextPosition());
    m_themeVolumeText.setString("Theme Vol");

    setRenderOrder(20);
	m_continue.setRenderOrder(21);
	m_exit.setRenderOrder(30);
	m_title.setRenderOrder(30);
    m_totalVolumeText.setRenderOrder(30);
	m_themeVolumeText.setRenderOrder(30);
    m_continue.getTextView().setRenderOrder(40);
    m_exit.getTextView().setRenderOrder(40);
    m_totalVolume.setRenderOrder(40);
    m_themeVolume.setRenderOrder(40);
}

Panel::~Panel()
{
}

void Panel::update()
{
	sf::View view = GameManager::getInstance()->getRenderWindow().getView();
    m_background.setPosition(sf::Vector2f(view.getCenter().x - m_background.getSize().x / 2.0f, view.getCenter().y - m_background.getSize().y / 2.0f));
    m_background2.setPosition(sf::Vector2f(m_background.getPosition().x + 10.0f, m_background.getPosition().y + 10.0f));
    m_continue.setPosition(getContinueButtonPosition());
	m_exit.setPosition(getExitButtonPosition());
	m_title.getComponent<Transform2D>().setPosition(getTitlePosition());
    m_totalVolume.setPostion(getTotalVolumePosition());
    m_themeVolume.setPostion(getThemeVolumePosition());
	m_totalVolumeText.getComponent<Transform2D>().setPosition(getTotalVolumeTextPosition());
	m_themeVolumeText.getComponent<Transform2D>().setPosition(getThemeVolumeTextPosition());
}

void Panel::render()
{
	GameManager::getInstance()->getRenderWindow().draw(m_background);
    GameManager::getInstance()->getRenderWindow().draw(m_background2);
}


