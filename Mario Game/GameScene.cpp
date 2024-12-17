#include "GameScene.hpp"
#include "QuestionBlock.hpp"
#include "Brick.hpp"

GameScene::GameScene(const string& mapPath) : m_mario(this) {
	m_renderOrder = 2;
	addComponent<SoundComponent>();

	m_map.setParent(this);
	m_map.loadFromJsonFile(mapPath);

	m_mario.getComponent<Transform2D>().setPosition(3000, 350);

	m_coinsText.setParent(this);
	m_scoreText.setParent(this);
	m_livesText.setParent(this);
	m_countdownText.setParent(this);
	m_worldNameText.setParent(this);

	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getWorldCenter().x, m_map.getStartDepth() * 240 + 120);
	
	float textWidth = view.getSize().x / 5;

	m_scoreText.setTable(FRect(0, 0, textWidth, 32));
	m_coinsText.setTable(FRect(textWidth, 0, textWidth, 32));
	m_worldNameText.setTable(FRect(textWidth * 2, 0, textWidth, 32));
	m_countdownText.setTable(FRect(textWidth * 3, 0, textWidth, 32));
	m_livesText.setTable(FRect(textWidth * 4, 0, textWidth, 32));

	m_scoreText.setString("SCORE\n0");
	m_coinsText.setString("COINS\n0");
	m_worldNameText.setString("WORLD\n1-1");
	m_countdownText.setString("TIME\n400");
	m_livesText.setString("LIVES\n3");
}

GameScene::~GameScene() {}

void GameScene::update() {

	View& view = GameManager::getInstance()->getView();
	float x = max(m_mario.getComponent<Transform2D>().getWorldPosition().x, view.getSize().x / 2);
	x = min(x, (float)m_map.getSize().x - view.getSize().x / 2);
	view.setCenter(x, view.getCenter().y);

	Transform2D& marioTF = m_mario.getComponent<Transform2D>();
	float xPos = max(marioTF.getPosition().x, marioTF.getPosition().x - marioTF.left);
	xPos = min(xPos, m_map.getSize().x - marioTF.right + marioTF.getPosition().x);
	marioTF.setPosition(xPos, marioTF.getPosition().y);
}

void GameScene::render() {

}

void GameScene::handleEvent(const Event& event) {

}

void GameScene::loadMap(const string& filename) {
	m_map.loadFromJsonFile(filename);
}