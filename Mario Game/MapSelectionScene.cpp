#include "MapSelectionScene.hpp"
#include "FontManager.hpp"
#include "GameManager.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"
#include "GameScene.hpp"

MapSelectionScene::MapSelectionScene()
{
	m_curChosenMap = 0;

	// SET BACKGROUND
	m_background.setTexture(TextureManager::getTexture("Resources/Thumbnails/Worlds-1-1.png"));
	this->fitBackground(&m_background, GameManager::getInstance()->getRenderWindow());

	m_prevBtn.setParent(this);
	m_nextBtn.setParent(this);
	m_confirmBtn.setParent(this);

	View& view = GameManager::getInstance()->getView();
	view.setCenter(view.getSize() / 2.0f);

	m_prevBtn.configure(Vector2f(0, view.getSize().y / 2), Vector2f(16, 16), "", FontManager::getInstance()->getFont("ARIAL"));
	m_nextBtn.configure(Vector2f(view.getSize().x - 70, view.getCenter().y), Vector2f(16, 16), "", FontManager::getInstance()->getFont("ARIAL"));
	m_confirmBtn.configure(Vector2f(view.getCenter().x, view.getSize().y - 30), Vector2f(50, 20), "Start!", FontManager::getInstance()->getFont("ARIAL"));

	m_prevBtn.getComponent<Transform2D>().setRect(60, view.getCenter().y, 16, 16);
	m_nextBtn.getComponent<Transform2D>().setRect(view.getSize().x - 60, view.getCenter().y, 16, 16);
	m_confirmBtn.getComponent<Transform2D>().setRect(view.getCenter().x, view.getSize().y - 20, 50, 20);

	m_prevBtn.setTexture(TextureManager::getTexture("Resources/UI/prev_button.png"));
	m_nextBtn.setTexture(TextureManager::getTexture("Resources/UI/next_button.png"));
	m_prevBtn.getBackground().scale(0.5, 0.5);
	m_nextBtn.getBackground().scale(0.5, 0.5);

	m_prevBtn.getText().setCharacterSize(12);
	m_nextBtn.getText().setCharacterSize(12);
	m_confirmBtn.getText().setCharacterSize(12);

	m_confirmBtn.setTextViewFillColor(Color::Red);
	m_confirmBtn.setButtonFillColor(Color::Yellow);
	m_confirmBtn.setRenderOrder(1);

	m_prevBtn.setAction([&]() { 
			if (m_curChosenMap > 0) {
				m_curChosenMap--;
				m_thumbnail.setTexture(Map::mapsInfo[m_curChosenMap].thumbnail);
				m_mapName.setString(string("World ") + Map::mapsInfo[m_curChosenMap].name);
			}
		});

	m_nextBtn.setAction([&]() {
			if (m_curChosenMap < 4) {
				m_curChosenMap++;
				m_thumbnail.setTexture(Map::mapsInfo[m_curChosenMap].thumbnail);
				m_mapName.setString(string("World ") + Map::mapsInfo[m_curChosenMap].name);
			}
		});

	m_confirmBtn.setAction([&]() { loadGameScene(Map::mapsInfo[m_curChosenMap]); });

	m_thumbnail.setParent(this);
	m_thumbnail.setRenderOrder(5);
	m_thumbnail.setAnchor(0.5, 0.5);
	m_thumbnail.getComponent<Transform2D>().setSize(50, 50);
	m_thumbnail.getComponent<Transform2D>().setWorldPosition(view.getCenter());
	m_thumbnail.setTexture(TextureManager::getTexture("Resources/Thumbnails/Worlds-1-1.png"));
	m_thumbnail.setOutlineThickness(4);
	m_thumbnail.setOutlineColor(Color::Yellow);

	m_mapName.setParent(this);
	m_mapName.setFont(FontManager::getInstance()->getFont("ARIAL"));
	m_mapName.setCharacterSize(15);
	m_mapName.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_mapName.getComponent<Transform2D>().setPosition(view.getCenter().x, 20);
	m_mapName.getComponent<Transform2D>().setSize(50, 16);
	m_mapName.setString("World 1-1");
	//m_mapName.alignCenter();

	m_background.scale(view.getSize().x / m_background.getGlobalBounds().width, view.getSize().y / m_background.getGlobalBounds().height);
}

MapSelectionScene::~MapSelectionScene() {}

void MapSelectionScene::update()
{
	
}

void MapSelectionScene::render()
{

}

void MapSelectionScene::handleEvent(const sf::Event& event)
{
	if (event.type == Event::Resized)
	{
		// ... Finish Later
	}
}

void MapSelectionScene::loadGameScene(const MapInfo& mapInfo) {
	SceneManager::getInstance()->setCurrentScene<GameScene>(mapInfo);
}