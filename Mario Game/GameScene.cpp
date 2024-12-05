#include "GameScene.hpp"

GameScene::GameScene() : m_mario(this), m_jumper(Vector2f(100, 208), this), m_flagpole(170, 32, 2, 160, this) {
	m_renderOrder = 2;

	m_map.setParent(this);
	m_map.loadFromJsonFile("Resources/Map/Worlds-1-1.json");
	//m_map.destroy();
	//m_map2.loadFromJsonFile("Resources/Map/Worlds-1-1.json");

	//Beanstalk* beanstalk = new Beanstalk({ 220, 200 }, 64, { 0, 100 });
	BalanceLifts* lift = new BalanceLifts({ 400, 100 }, { 500, 120 }, 50, 20, 0.002f);
	lift->setParent(this);
}

GameScene::~GameScene() {}

void GameScene::update() {
	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getWorldPosition().x, view.getCenter().y);
}

void GameScene::render() {

}

void GameScene::handleEvent(const Event& event) {

}

void GameScene::loadMap() {
	m_map.loadFromJsonFile("Resources/Map/Worlds-1-1.json");
}