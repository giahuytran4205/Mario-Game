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

class GameScene : public Scene {
private:
	Mario m_mario;
	Map m_map, m_map2;
	Jumper m_jumper;
	FlagPole m_flagpole;

public:
	GameScene();
	~GameScene();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
	void loadMap();
};