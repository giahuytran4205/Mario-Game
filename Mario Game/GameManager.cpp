#include "GameManager.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "LoginScene.hpp"
#include "GameScene.hpp"
#include "MapSelectionScene.hpp"
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
	m_window.create(VideoMode(1200, 600), "Super Mario Bros. (1985)", Style::Default);
	m_window.setFramerateLimit(120);

	m_collisionManager = { Vector2i(3376, 480), 16};

	m_view.reset(FloatRect(0, 0, getAspectRatio() * 208, 208));

	m_view.setCenter(0, m_view.getSize().y / 2 + 16);

	m_view.setViewport(FloatRect(0, 0, 1, 1));
	m_window.setView(m_view);

	m_sceneManager.setCurrentScene<MapSelectionScene>();
}

void GameManager::start() {
	while (m_window.isOpen())
	{
		m_window.clear();

		m_deltaTime = min(m_clock.getElapsedTime(), milliseconds(10));
		m_clock.restart();

		m_window.setView(m_view);

		m_eventSystem.handleEvents();

		m_entitiesManager.update();

		m_collisionManager.update();

		m_coroutineManager.update();

		m_entitiesManager.render();

#if DEBUG

		m_window.draw(Transform2D::rectangles);
		Transform2D::rectangles.clear();

#endif // DEBUG

		m_window.display();
	}
}

void GameManager::pause()
{
}

void GameManager::render() {

}

void GameManager::destroy() {

}

void GameManager::handleEvent(const Event& event) {
	if (event.type == Event::Closed) {
		m_window.close();
	}

	if (event.type == Event::Resized) {
		m_view.setSize(208.0f * event.size.width / event.size.height, 208);
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

View& GameManager::getView() {
	return m_view;
}

float GameManager::getAspectRatio() {
	return (float)m_window.getSize().x / m_window.getSize().y;
}