#pragma once
#include "Scene.hpp"
#include "Coroutine.hpp"
#include "GameManager.hpp"
#include "Map.hpp"
#include "Mario.hpp"
#include "Jumper.hpp"
#include "FlagPole.hpp"
#include "Beanstalk.hpp"
#include "Lift.hpp"
#include "BalanceLifts.hpp"
#include "Slider.hpp"
#include "TextView.hpp"
#include "Panel.hpp"

class GameScene : public Scene {
private:
	Mario m_mario;
	Map m_map;
	Panel m_optionPanel;
	Object m_canvas;
	TextView m_coinsText[2];
	TextView m_scoreText[2];
	TextView m_livesText[2];
	TextView m_countdownText[2];
	TextView m_worldNameText[2];

public:
	GameScene(const MapInfo& mapPath);
	~GameScene();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
	void loadMap(const string& filename);
	Panel& getOptionPanel();
	void setEnableOptionPanel(bool isEnable);
};