#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "Mario.hpp"
#include "EventSystem.hpp"
using namespace sf;

class GameManager : IEventListener {
private:
	static GameManager* m_instance;
	EntitiesManager m_entitiesManager;
	TextureManager m_textureManager;
	Mario* m_player = nullptr;
	RenderWindow m_window;
	EventSystem m_eventSystem;

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
	RenderWindow& getRenderWindow();
};