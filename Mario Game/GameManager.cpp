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
#include "Item.hpp"
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

	m_eventSystem.addListener(this);

	m_player = new Mario();
	m_map = new Map();
	m_map->loadFromJsonFile("Resources/Map/Worlds-1-1.json");

	Texture* texture = new Texture();
	texture->loadFromFile("Resources/Background/Worlds-1-1.png");

	m_map->setBackground(*texture);

	m_collisionManager = { m_map->getSize(), 16};

	m_view.reset(FloatRect(0, 0, getAspectRatio() * 208, 208));

	m_view.setViewport(FloatRect(0, 0, 1, 1));

	m_view.setCenter(0, m_view.getSize().y / 2 + 16);
	
	m_window.setView(m_view);

	Jumper* jumper = new Jumper(Vector2f(100, 208));
	/*
	//m_flagPole = new FlagPole(170, 32, 16, 160);
	m_billBlaster = new Enemy(EnemyType::BILL_BLASTER, Color(169, 169, 169), Vector2f(16, 32)); // Darker gray, cao hơn
	m_billBlaster->getTransform2D().setPosition(350, 208);

	m_piranhaPlant = new Enemy(EnemyType::PIRANHA_PLANT, Color(50, 205, 50), Vector2f(16, 24)); // Lime green
	m_piranhaPlant->getTransform2D().setPosition(400, 208);

	// Basic ground enemies
	m_goomba = new Enemy(EnemyType::GOOMBA, Color(139, 69, 19), Vector2f(16, 16)); // Brown
	m_goomba->getTransform2D().setPosition(450, 208);

	m_koopaTroopa = new Enemy(EnemyType::KOOPA_TROOPA, Color::Red, Vector2f(16, 24)); // Cao hơn Goomba
	m_koopaTroopa->getTransform2D().setPosition(500, 208);

	m_buzzyBeetle = new Enemy(EnemyType::BUZZY_BEETLE, Color(128, 0, 128), Vector2f(16, 16)); // Purple
	m_buzzyBeetle->getTransform2D().setPosition(550, 208);

	// Flying enemies
	m_koopaParatroopa = new Enemy(EnemyType::KOOPA_PARATROOPA, Color::Red, Vector2f(16, 24));
	m_koopaParatroopa->getTransform2D().setPosition(600, 180); // Bay cao hơn mặt đất

	m_cheepCheep = new Enemy(EnemyType::CHEEP_CHEEP, Color::Red, Vector2f(16, 16));
	m_cheepCheep->getTransform2D().setPosition(650, 160);

	m_lakitu = new Enemy(EnemyType::LAKITU, Color::Yellow, Vector2f(16, 24));
	m_lakitu->getTransform2D().setPosition(700, 150);

	// Special enemies
	m_hammerBro = new Enemy(EnemyType::HAMMER_BRO, Color(255, 140, 0), Vector2f(16, 24)); // Orange
	m_hammerBro->getTransform2D().setPosition(750, 208);

	m_spiny = new Enemy(EnemyType::SPINY, Color(255, 69, 0), Vector2f(16, 16)); // Red-orange
	m_spiny->getTransform2D().setPosition(800, 208);

	m_spinyEgg = new Enemy(EnemyType::SPINY_EGG, Color(255, 192, 203), Vector2f(16, 16)); // Pink
	m_spinyEgg->getTransform2D().setPosition(850, 208);

	m_bulletBill = new Enemy(EnemyType::BULLET_BILL, Color::Black, Vector2f(16, 16));
	m_bulletBill->getTransform2D().setPosition(900, 208);

	m_blooper = new Enemy(EnemyType::BLOOPER, Color::White, Vector2f(16, 24));
	m_blooper->getTransform2D().setPosition(950, 180);

	m_lavaBubble = new Enemy(EnemyType::LAVA_BUBBLE, Color(255, 69, 0), Vector2f(16, 16)); // Red-orange
	m_lavaBubble->getTransform2D().setPosition(1000, 208);
	*/
	
	m_oneUpMushroom = new Item(50, 0, 16, 16, ItemType::OneUpMushroom);
	m_oneUpMushroom->setPosition(Vector2f(50, 208));
	m_magicMushroom = new Item(100, 0, 16, 16, ItemType::MagicMushroom);
	m_magicMushroom->setPosition(Vector2f(100, 208));
	m_fireFlower = new Item(150, 0, 16, 16, ItemType::FireFlower);
	m_fireFlower->setPosition(Vector2f(150, 208));
	m_starman = new Item(200, 0, 16, 16, ItemType::Starman);
	m_starman->setPosition(Vector2f(200, 208));
	m_koopaShell = new Item(250, 0, 16, 16, ItemType::KoopaShell);
	m_koopaShell->setPosition(Vector2f(250, 208));
	m_buzyShell = new Item(300, 0, 16, 16, ItemType::BuzyShell);
	m_buzyShell->setPosition(Vector2f(300, 208));
	

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

		m_view.setCenter(m_player->getComponent<Transform2D>().getPosition().x, m_view.getCenter().y);

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