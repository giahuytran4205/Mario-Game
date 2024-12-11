#include "GameScene.hpp"
#include "Slider.hpp"

GameScene::GameScene(const string& mapPath) : m_mario(this), m_slider(0, 100, 50, 0, { 100, 350 }, this) {
	m_renderOrder = 2;

	m_map.setParent(this);
	m_map.loadFromJsonFile(mapPath);

	m_mario.getComponent<Transform2D>().setPosition(m_map.getSpawnPos());

	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getWorldCenter().x, m_map.getStartDepth() * 240 + 120);
}

GameScene::~GameScene() {}

void GameScene::update() {
	View& view = GameManager::getInstance()->getView();
	float x = max(m_mario.getComponent<Transform2D>().getWorldPosition().x, view.getSize().x / 2);
	x = min(x, (float)m_map.getSize().x - view.getSize().x / 2);
	view.setCenter(x, view.getCenter().y);
}

void GameScene::render() {

}

void GameScene::handleEvent(const Event& event) {

}

void GameScene::loadMap(const string& filename) {
	m_map.loadFromJsonFile(filename);
}