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

class GameScene : public Scene {
private:
	Mario m_mario;
	Map m_map;
	Slider<float> m_slider;

public:
	GameScene(const string& mapPath);
	~GameScene();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
	void loadMap(const string& filename);
};