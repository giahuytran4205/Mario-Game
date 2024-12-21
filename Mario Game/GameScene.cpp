#include "GameScene.hpp"
#include "QuestionBlock.hpp"
#include "Brick.hpp"

GameScene::GameScene(const MapInfo& mapInfo) : m_mario(this) {
	m_renderOrder = 2;
	addComponent<SoundComponent>();

	m_map.setParent(this);
	m_map.loadFromJsonFile(mapInfo.path);

	m_mario.getComponent<Transform2D>().setPosition(m_map.getSpawnPos());

	m_canvas.setParent(this);

	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getWorldCenter().x, m_map.getStartDepth() * 240 + 120);
	
	float textWidth = view.getSize().x / 5;

	m_scoreText[0].setTable(FRect(0, 0, textWidth, 16));
	m_coinsText[0].setTable(FRect(textWidth, 0, textWidth, 16));
	m_worldNameText[0].setTable(FRect(textWidth * 2, 0, textWidth, 16));
	m_countdownText[0].setTable(FRect(textWidth * 3, 0, textWidth, 16));
	m_livesText[0].setTable(FRect(textWidth * 4, 0, textWidth, 16));

	m_scoreText[1].setTable(FRect(0, 16, textWidth, 16));
	m_coinsText[1].setTable(FRect(textWidth, 16, textWidth, 16));
	m_worldNameText[1].setTable(FRect(textWidth * 2, 16, textWidth, 16));
	m_countdownText[1].setTable(FRect(textWidth * 3, 16, textWidth, 16));
	m_livesText[1].setTable(FRect(textWidth * 4, 16, textWidth, 16));

	for (int i = 0; i < 2; i++) {
		m_coinsText[i].setParent(&m_canvas);
		m_scoreText[i].setParent(&m_canvas);
		m_livesText[i].setParent(&m_canvas);
		m_countdownText[i].setParent(&m_canvas);
		m_worldNameText[i].setParent(&m_canvas);

		m_scoreText[i].setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));
		m_coinsText[i].setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));
		m_worldNameText[i].setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));
		m_countdownText[i].setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));
		m_livesText[i].setFont(FontManager::getInstance()->getFont("SUPERMARIO256"));

		m_scoreText[i].setFillColor(Color::White);
		m_coinsText[i].setFillColor(Color::White);
		m_worldNameText[i].setFillColor(Color::White);
		m_countdownText[i].setFillColor(Color::White);
		m_livesText[i].setFillColor(Color::White);

		m_scoreText[i].alignCenter();
		m_coinsText[i].alignCenter();
		m_worldNameText[i].alignCenter();
		m_countdownText[i].alignCenter();
		m_livesText[i].alignCenter();

		m_scoreText[i].setCharacterSize(15);
		m_coinsText[i].setCharacterSize(15);
		m_worldNameText[i].setCharacterSize(15);
		m_countdownText[i].setCharacterSize(15);
		m_livesText[i].setCharacterSize(15);

		/*m_scoreText[i].setScale(0.5, 0.5);
		m_coinsText[i].setScale(0.5, 0.5);
		m_worldNameText[i].setScale(0.5, 0.5);
		m_countdownText[i].setScale(0.5, 0.5);
		m_livesText[i].setScale(0.5, 0.5);*/
	}

	m_scoreText[0].setString("SCORE");
	m_coinsText[0].setString("COINS");
	m_worldNameText[0].setString("WORLD");
	m_countdownText[0].setString("TIME");
	m_livesText[0].setString("LIVES");
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

	m_canvas.getComponent<Transform2D>().setPosition(view.getCenter() - view.getSize() / 2.0f);

	m_scoreText[1].setString(to_string(m_mario.getScore()));
	m_coinsText[1].setString(to_string(m_mario.getCoins()));
	m_worldNameText[1].setString("2-1");
	m_countdownText[1].setString(to_string((int)m_mario.getCountdownTime().asSeconds()));
	m_livesText[1].setString(to_string(m_mario.getLives()));
}

void GameScene::render() {

}

void GameScene::handleEvent(const Event& event) {

}

void GameScene::loadMap(const string& filename) {
	m_map.loadFromJsonFile(filename);
}