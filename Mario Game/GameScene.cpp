#include "GameScene.hpp"
#include "GameManager.hpp"

GameScene::GameScene() : m_mario(this), m_jumper(Vector2f(100, 208), this), m_flagpole(170, 32, 2, 160, this) {
	m_renderOrder = 2;

	m_map.loadFromJsonFile("Resources/Map/Worlds-1-1.json");

	Texture* texture = new Texture();
	texture->loadFromFile("Resources/Background/Worlds-1-1.png");

	m_map.setBackground(*texture);

	Beanstalk* beanstalk = nullptr;

	//sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	//sf::View& view = GameManager::getInstance()->getView();

	//view.reset(FloatRect(0, 0, GameManager::getInstance()->getAspectRatio() * 208, 208));

	//view.setCenter(0, view.getSize().y / 2 + 16);

	//view.setViewport(FloatRect(0, 0, 1, 1));
	//window.setView(view);
}

GameScene::~GameScene() {}

void GameScene::update() {
	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getPosition().x, view.getCenter().y);
}

void GameScene::render() {

}

void GameScene::handleEvent(const Event& event) {

}