#pragma once
#include "Mario.hpp"
#include "Block.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "TextureManager.hpp"

class GameManager {
private:
	static GameManager* m_instance;
	EntitiesManager m_entitiesManager;
	TextureManager m_textureManager;
	Mario* m_player = nullptr;
	RenderWindow m_window;

public:
	GameManager();
	~GameManager();

	void init();
	void start();
	void pause();
	void render();
	void destroy();
	static GameManager* getInstance();
	RenderWindow& getRenderWindow();
};