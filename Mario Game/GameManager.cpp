#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "Mario.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Toggle.hpp"
#include "SpriteRenderer.hpp"
#include "EventSystem.hpp"
using namespace sf;
using namespace std;

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager() : m_eventSystem(m_window) {
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

	m_eventSystem.addListener(this);

	m_player = new Mario();
	Map* map = new Map();
	map->loadBitmap("Resources/test_map.csv");
	map->drawMap();

	Texture* texture1 = new Texture(), *texture2 = new Texture();
	texture1->loadFromFile("Goomba.png");
	texture2->loadFromFile("Resources/Blocks/brick.png");
	Toggle* option1 = new Toggle(m_window, *texture1, *texture2);
	option1->getComponent<Transform2D>().getRect() = { 0, 0, 50, 50 };
	option1->getComponent<Transform2D>().setPosition({ 50, 100 });
}

void GameManager::start() {
	while (m_window.isOpen())
	{
		m_eventSystem.handleEvents();

		m_window.clear();

		m_entitiesManager.update();

		m_window.display();
	}
}

void GameManager::render() {

}

void GameManager::destroy() {

}

void GameManager::handleEvent(const Event& event) {
	if (event.type == Event::Closed) {
		m_window.close();
	}
}

GameManager* GameManager::getInstance() {
	return m_instance;
}

RenderWindow& GameManager::getRenderWindow() {
	return m_window;
}