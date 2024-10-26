#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
#include "Mario.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
using namespace sf;
using namespace std;

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager () {
	if (!m_instance) {
		m_instance = this;
	}
	else {
		m_instance->destroy();
		m_instance = this;
	}
	init();
}

GameManager::~GameManager() {

}

void GameManager::init() {
	m_window.create(VideoMode(600, 600), "Super Mario Bros. (1985)", Style::Default);
	m_window.setFramerateLimit(120);

	m_player = new Mario();
	Map* map = new Map();
	map->loadBitmap("Resources/test_map.csv");
	map->drawMap();
	/*brick[10] = new Brick();
	brick[10]->getComponent<Transform2D>().setPosition({ 50.0f, 190 });*/
}

void GameManager::start() {
	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				m_window.close();
		}

		m_window.clear();

		m_entitiesManager.update();

		m_window.display();
	}
}

void GameManager::render() {

}

void GameManager::destroy() {

}

GameManager* GameManager::getInstance() {
	return m_instance;
}

RenderWindow& GameManager::getRenderWindow() {
	return m_window;
}