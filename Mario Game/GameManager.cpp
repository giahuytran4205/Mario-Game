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
#include "Collision.hpp"
#include <iostream>
using namespace sf;
using namespace std;

GameManager* GameManager::m_instance = nullptr;
Time GameManager::m_deltaTime;

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
	m_window.create(VideoMode(1200, 480), "Super Mario Bros. (1985)", Style::Default);
	m_window.setFramerateLimit(120);

	m_eventSystem.addListener(this);

	m_player = new Mario();
	Map* map = new Map();
	map->loadFromJsonFile("D:/GHuy/OOP/Tile/Worlds-1-1.json");

	m_collisionManager = { map->getSize(), 16};

	m_view.reset(FloatRect(0, 0, 1200, 480));

	m_view.setViewport(FloatRect(0, 0, 1, 1));
	m_window.setView(m_view);

}

void GameManager::start() {
	while (m_window.isOpen())
	{
		m_window.clear();

		m_deltaTime = m_clock.getElapsedTime();
		m_clock.restart();

		m_window.setView(m_view);

		m_eventSystem.handleEvents();

		m_entitiesManager.update();

		m_collisionManager.update();

		m_view.setCenter({ m_player->getComponent<Transform2D>().getPosition().x, m_view.getCenter().y });

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

Time& GameManager::getDeltaTime() {
	return m_deltaTime;
}

RenderWindow& GameManager::getRenderWindow() {
	return m_window;
}