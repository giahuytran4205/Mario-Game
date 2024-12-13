#include "GameScene.hpp"
#include "QuestionBlock.hpp"
#include "Brick.hpp"

GameScene::GameScene(const string& mapPath) : m_mario(this) {
	m_renderOrder = 2;
	addComponent<SoundComponent>();

	m_map.setParent(this);
	m_map.loadFromJsonFile(mapPath);

	m_mario.getComponent<Transform2D>().setPosition(3000, 350);

	View& view = GameManager::getInstance()->getView();
	view.setCenter(m_mario.getComponent<Transform2D>().getWorldCenter().x, m_map.getStartDepth() * 240 + 120);

	QuestionBlock* block = new QuestionBlock(OVERWORLD, this);
	block->getComponent<Transform2D>().setPosition(50, 380);

	m_countdown = 300;
}

GameScene::~GameScene() {}

void GameScene::update() {
	if (m_countdown > 0)
		m_countdown -= deltaTime.asSeconds();

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

void GameScene::win() {
	int numFirework = randRange(5, 10);
	for (int i = 0; i < numFirework; i++) {
		float x = randRange(m_map.getFireworkArea().left, m_map.getFireworkArea().right);
		float y = randRange(m_map.getFireworkArea().top, m_map.getFireworkArea().bottom);

		ParticleSystem::getInstance()->addParticle("Resources/Particles/Firework.json", Vector2f(0, 0));
	}
}