#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "SoundBufferManager.hpp"
#include "EventSystem.hpp"
#include "Collision.hpp"
#include "SceneManager.hpp"
using namespace sf;

#define deltaTime GameManager::getDeltaTime()

class GameManager : IEventListener {
private:
	static GameManager* m_instance;
	EntitiesManager m_entitiesManager;
	TextureManager m_textureManager;
	SoundBufferManager m_soundBufferManager;
	CollisionManager m_collisionManager;
	SceneManager m_sceneManager;
	EventSystem m_eventSystem;
	RenderWindow m_window;
	View m_view;
	Clock m_clock;
	static Time m_deltaTime;

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