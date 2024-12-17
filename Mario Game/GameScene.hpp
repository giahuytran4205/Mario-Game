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

class GameScene : public Scene {
private:
	Mario m_mario;
	Map m_map;
	TextView m_coinsText;
	TextView m_scoreText;
	TextView m_livesText;
	TextView m_countdownText;
	TextView m_worldNameText;

public:
	GameScene(const string& mapPath);
	~GameScene();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
	void loadMap(const string& filename);
};