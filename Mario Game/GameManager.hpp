#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "SoundBufferManager.hpp"
#include "Mario.hpp"
#include "EventSystem.hpp"
#include "Collision.hpp"
#include "Toggle.hpp"
#include "Slider.hpp"
#include "Map.hpp"
#include "FlagPole.hpp"
#include "Item.hpp"
#include "enemy.hpp"
using namespace sf;

#define deltaTime GameManager::getDeltaTime()

class GameManager : IEventListener {
private:
	static GameManager* m_instance;
	EntitiesManager m_entitiesManager;
	TextureManager m_textureManager;
	SoundBufferManager m_soundBufferManager;
	CollisionManager m_collisionManager;
	EventSystem m_eventSystem;
	RenderWindow m_window;
	View m_view;
	Clock m_clock;
	static Time m_deltaTime;

	Mario* m_player = nullptr;
	Map* m_map = nullptr;
	FlagPole* m_flagPole = nullptr;
	//Toggle m_toggle;
	//Slider m_slider;
	//Object* m_test = nullptr;


	// Add all item pointers
	Item* m_oneUpMushroom = nullptr;
	Item* m_magicMushroom = nullptr;
	Item* m_fireFlower = nullptr;
	Item* m_starman = nullptr;
	Item* m_koopaShell = nullptr;
	Item* m_buzyShell = nullptr;

	Enemy* m_billBlaster = nullptr;
	Enemy* m_piranhaPlant = nullptr;
	Enemy* m_goomba = nullptr;
	Enemy* m_koopaTroopa = nullptr;
	Enemy* m_buzzyBeetle = nullptr;
	Enemy* m_koopaParatroopa = nullptr;
	Enemy* m_cheepCheep = nullptr;
	Enemy* m_lakitu = nullptr;
	Enemy* m_hammerBro = nullptr;
	Enemy* m_spiny = nullptr;
	Enemy* m_spinyEgg = nullptr;
	Enemy* m_bulletBill = nullptr;
	Enemy* m_blooper = nullptr;
	Enemy* m_lavaBubble = nullptr;

public:
	GameManager();
	~GameManager();

	void init();
	void start();
	void pause();
	void render();
	void destroy();
	void handleEvent(const Event& event) override;
	static GameManager* getInstance();
	static Time& getDeltaTime();
	RenderWindow& getRenderWindow();
	View& getView();
	float getAspectRatio();
};