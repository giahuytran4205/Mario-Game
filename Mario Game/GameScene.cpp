#include "GameScene.hpp"
#include "GameManager.hpp"

GameScene::GameScene() : m_mario(this), m_jumper(Vector2f(100, 208), this), m_flagpole(170, 32, 2, 160, this) {
	m_renderOrder = 2;

	m_map.setParent(this);
	m_map.loadFromJsonFile("Resources/Map/Worlds-1-1.json");

	Texture* texture = new Texture();
	texture->loadFromFile("Resources/Background/Worlds-1-1.png");

	m_map.setBackground(*texture);

	Beanstalk* beanstalk = new Beanstalk({ 220, 200 }, 64, { 0, 100 });
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