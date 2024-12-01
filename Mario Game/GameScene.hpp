#pragma once
#include "Scene.hpp"
#include "Mario.hpp"
#include "Map.hpp"
#include "Jumper.hpp"
#include "FlagPole.hpp"
#include "Beanstalk.hpp"

class GameScene : public Scene {
private:
	Mario m_mario;
	Map m_map;
	Jumper m_jumper;
	FlagPole m_flagpole;

public:
	GameScene();
	~GameScene();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
};