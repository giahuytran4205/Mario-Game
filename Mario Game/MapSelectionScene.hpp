#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include "TextView.hpp"
#include "InputField.hpp"
#include "Map.hpp"
#include "Coin.hpp"

constexpr float MAPSELECTIONSCENE_SPACE_DISTANCE = 25.0f;

class MapSelectionScene : public Scene
{
private:
	Button m_prevBtn;
	Button m_nextBtn;
	Button m_confirmBtn;
	SpriteRenderer m_thumbnail;
	SpriteRenderer m_background;
	TextView m_mapName;
	int m_curChosenMap;

public:
	MapSelectionScene();
	~MapSelectionScene();

	void update();
	void render();
	void handleEvent(const sf::Event& event);
	void loadGameScene(const MapInfo& mapInfo);
};
