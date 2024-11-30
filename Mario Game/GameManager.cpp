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
#include "Jumper.hpp"
#include "FlagPole.hpp"
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
	//m_window.create(VideoMode(1200, 480), "Super Mario Bros. (1985)", Style::Default);
	//m_window.setFramerateLimit(120);

	//m_eventSystem.addListener(this);

	//m_player = new Mario();
	//m_map = new Map();
	//m_map->loadFromJsonFile("Resources/Map/Worlds-1-1.json");

	//Texture* texture = new Texture();
	//texture->loadFromFile("Resources/Background/Worlds-1-1.png");

	//m_map->setBackground(*texture);

	//m_collisionManager = { m_map->getSize(), 16};

	//m_view.reset(FloatRect(0, 0, getAspectRatio() * 208, 208));

	//m_view.reset(FloatRect(0, 0, 1200, 480));

	//m_view.setViewport(FloatRect(0, 0, 1, 1));

	//m_view.setCenter(0, m_view.getSize().y / 2 + 16);
	//
	//m_window.setView(m_view);

	//Jumper* jumper = new Jumper(Vector2f(100, 208));

	//m_flagPole = new FlagPole(170, 32, 2, 160);

	m_window.create(VideoMode(1200, 600), "Super Mario Bros. (1985)", Style::Default);
	m_window.setFramerateLimit(120);

	m_eventSystem.addListener(this);

	m_player = new Mario();
	Map* map = new Map();
	map->loadFromJsonFile("Resources\\Map\\Worlds-1-1.json");

	m_collisionManager = { map->getSize(), 16 };

	m_view.reset(FloatRect(0, 0, 1200, 600));

	m_view.setViewport(FloatRect(0, 0, 1, 1));
	m_window.setView(m_view);

	m_fontManager = new FontManager();
}

void GameManager::start() {
	/*
	while (m_window.isOpen())
	{
		m_window.clear();

		m_deltaTime = m_clock.getElapsedTime();
		m_clock.restart();

		m_window.setView(m_view);

		m_eventSystem.handleEvents();

		m_entitiesManager.update();

		m_collisionManager.update();

		m_view.setCenter(m_player->getComponent<Transform2D>().getPosition().x, m_view.getCenter().y);

		m_window.display();
	}
	*/

	float newTime, frameTime, interpolation; // interpolation: smooth movement between frames

	m_deltaTime = m_clock.getElapsedTime();
	float currentTime = m_deltaTime.asSeconds();
	float accumulator = 0.0f;

	std::unique_ptr<State> loginState = std::make_unique<LoginState>();

	m_stateManager.addState(std::move(loginState), false);

	while (m_window.isOpen())
	{
		m_stateManager.changeState();

		newTime = m_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= this->dT)
		{
			// Check if there's a state before polling events
			State* currentState = m_stateManager.peekState();

			if (currentState) {
				currentState->handleEvents();
				currentState->update(this->dT);
			}

			accumulator -= this->dT;

		}

		State* currentState = m_stateManager.peekState();

		if (currentState) {
			interpolation = accumulator / dT;
			currentState->render(interpolation);
		}
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